#include "clipper2/clipper.core.h"
#include "clipper2/clipper.h"
#include "clipper2/clipper.offset.h"
#include "clipper2/clipper.triangulation.h"
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;
using namespace Clipper2Lib;

template <typename T>
void ReversePath(Path<T>& path) {
    std::reverse(path.begin(), path.end());
}

#ifdef USINGZ
static_assert(sizeof(Point64) == 3 * sizeof(int64_t),
              "Path64_view/assign require USINGZ layout: Point64 == {x, y, z}");
static_assert(sizeof(PointD) == 3 * sizeof(double),
              "PathD_view/assign require USINGZ layout: PointD == {x, y, z}");

val Path64_view(const Path64& path) {
    return val(typed_memory_view(path.size() * 3,
                                 reinterpret_cast<const int64_t*>(path.data())));
}

val PathD_view(const PathD& path) {
    return val(typed_memory_view(path.size() * 3,
                                 reinterpret_cast<const double*>(path.data())));
}

void Path64_assign(Path64& path, val jsArray) {
    const unsigned len = jsArray["length"].as<unsigned>();
    if (len % 3 != 0) {
        throw std::runtime_error("Path64.assign: array length must be a multiple of 3");
    }
    const unsigned n = len / 3;
    path.resize(n);
    if (n > 0) {
        val view(typed_memory_view(n * 3, reinterpret_cast<int64_t*>(path.data())));
        view.call<void>("set", jsArray);
    }
}

void PathD_assign(PathD& path, val jsArray) {
    const unsigned len = jsArray["length"].as<unsigned>();
    if (len % 3 != 0) {
        throw std::runtime_error("PathD.assign: array length must be a multiple of 3");
    }
    const unsigned n = len / 3;
    path.resize(n);
    if (n > 0) {
        val view(typed_memory_view(n * 3, reinterpret_cast<double*>(path.data())));
        view.call<void>("set", jsArray);
    }
}
#endif // USINGZ


struct TriangulateResult64 {
    TriangulateResult result;
    Paths64 solution;
};

struct TriangulateResultD {
    TriangulateResult result;
    PathsD solution;
};

TriangulateResult64 Triangulate64(const Paths64& pp, bool useDelaunay) {
    TriangulateResult64 res;
    res.result = Triangulate(pp, res.solution, useDelaunay);
    return res;
}

TriangulateResultD TriangulateD(const PathsD& pp, int decPlaces, bool useDelaunay) {
    TriangulateResultD res;
    res.result = Triangulate(pp, decPlaces, res.solution, useDelaunay);
    return res;
}

Clipper64* CreateClipper64(bool preserveCollinear) {
    Clipper64* clipper = new Clipper64();
    clipper->PreserveCollinear(preserveCollinear);
    return clipper;
}

ClipperD* CreateClipperD(bool preserveCollinear) {
    ClipperD* clipper = new ClipperD();
    clipper->PreserveCollinear(preserveCollinear);
    return clipper;
}

// Wrapper for ClipperOffset delta callback from JavaScript
void ClipperOffset_SetDeltaCallback(ClipperOffset& co, val jsCallback) {
    co.SetDeltaCallback(
        [jsCallback](const Path64& path, const PathD& path_normals, size_t curr_idx, size_t prev_idx) -> double {
            return jsCallback(
                val(path),
                val(path_normals),
                val(static_cast<double>(curr_idx)),
                val(static_cast<double>(prev_idx))
            ).as<double>();
        }
    );
}

void ClipperOffset_ExecuteCallback(ClipperOffset& co, val jsCallback, Paths64& solution) {
    co.Execute(
        [jsCallback](const Path64& path, const PathD& path_normals, size_t curr_idx, size_t prev_idx) -> double {
            return jsCallback(
                val(path),
                val(path_normals),
                val(static_cast<double>(curr_idx)),
                val(static_cast<double>(prev_idx))
            ).as<double>();
        },
        solution
    );
}

EMSCRIPTEN_BINDINGS(clipper_module) {
        class_<ClipperBase>("ClipperBase")
        .function("Clear", &ClipperBase::Clear)
        .function("SetPreserveCollinear(preserveCollinear)", select_overload<void(bool)>(&ClipperBase::PreserveCollinear))
        .function("GetPreserveCollinear", select_overload<bool() const>(&ClipperBase::PreserveCollinear));

        enum_<FillRule>("FillRule")
        .value("EvenOdd", FillRule::EvenOdd)
        .value("NonZero", FillRule::NonZero)
        .value("Positive", FillRule::Positive)
        .value("Negative", FillRule::Negative);

        enum_<ClipType>("ClipType")
        .value("Intersection", ClipType::Intersection)
        .value("Union", ClipType::Union)
        .value("Difference", ClipType::Difference)
        .value("Xor", ClipType::Xor);

        enum_<PathType>("PathType")
        .value("Subject", PathType::Subject)
        .value("Clip", PathType::Clip);

        enum_<JoinType>("JoinType")
        .value("Square", JoinType::Square)
        .value("Round", JoinType::Round)
        .value("Miter", JoinType::Miter);

        enum_<EndType>("EndType")
        .value("Polygon", EndType::Polygon)
        .value("Joined", EndType::Joined)
        .value("Butt", EndType::Butt)
        .value("Square", EndType::Square)
        .value("Round", EndType::Round);

        enum_<PointInPolygonResult>("PointInPolygonResult")
        .value("IsOn", PointInPolygonResult::IsOn)
        .value("IsInside", PointInPolygonResult::IsInside)
        .value("IsOutside", PointInPolygonResult::IsOutside);

        enum_<TriangulateResult>("TriangulateResult")
        .value("Success", TriangulateResult::success)
        .value("Fail", TriangulateResult::fail)
        .value("NoPolygons", TriangulateResult::no_polygons)
        .value("PathsIntersect", TriangulateResult::paths_intersect);

        value_object<TriangulateResult64>("TriangulateResult64")
        .field("result", &TriangulateResult64::result)
        .field("solution", &TriangulateResult64::solution);

        value_object<TriangulateResultD>("TriangulateResultD")
        .field("result", &TriangulateResultD::result)
        .field("solution", &TriangulateResultD::solution);

        // #############################
        // ###### 64 bit bindings ######
        // #############################

	// Point64 bindings (for now only support USINGZ=ON)
	#ifdef USINGZ
	class_<Point64>("Point64")
        .constructor<int64_t, int64_t, int64_t>()
        .property("x", &Point64::x)
        .property("y", &Point64::y)
        .property("z", &Point64::z)
        .function("SetZ(z)", &Point64::SetZ);
	#endif

	// Path64
	class_<Path64>("Path64")
        .constructor<>()
        .function("size", &Path64::size)
        .function("clear", &Path64::clear)
        .function("resize(newSize)", select_overload<void(size_t)>(&Path64::resize))
        .function("push_back(point)", select_overload<void(const Point64&)>(&Path64::push_back))
        .function("get(index)", select_overload<Point64&(size_t)>(&Path64::operator[]), allow_raw_pointers())
#ifdef USINGZ
        .function("view", &Path64_view)
        .function("assign(coordinates)", &Path64_assign)
#endif
        ;

	// Paths64
	class_<Paths64>("Paths64")
        .constructor<>()
        .function("size", &Paths64::size)
        .function("clear", &Paths64::clear)
        .function("push_back(path)", select_overload<void(const Path64&)>(&Paths64::push_back))
        .function("get(index)", select_overload<Path64&(size_t)>(&Paths64::operator[]), allow_raw_pointers());

        // Misc64
        function("AreaPath64(path)", select_overload<double(const Path64&)>(&Area), allow_raw_pointers());
        function("AreaPaths64(paths)", select_overload<double(const Paths64&)>(&Area), allow_raw_pointers());
        function("IsPositive64(poly)", select_overload<bool(const Path64&)>(&IsPositive), allow_raw_pointers());
        function("PointInPolygon64(point, polygon)", select_overload<PointInPolygonResult(const Point64&, const Path64&)>(&PointInPolygon), allow_raw_pointers());
        function("ReversePath64(path)", &ReversePath<int64_t>, allow_raw_pointers());

        // Geometry64
        class_<Rect64>("Rect64")
        .constructor<>()
        .constructor<int64_t, int64_t, int64_t, int64_t>()
        .property("left", &Rect64::left)
        .property("top", &Rect64::top)
        .property("right", &Rect64::right)
        .property("bottom", &Rect64::bottom)
        .function("IsValid", &Rect64::IsValid)
        .function("Width", select_overload<int64_t() const>(&Rect<int64_t>::Width))
        .function("Height", select_overload<int64_t() const>(&Rect<int64_t>::Height))
        .function("MidPoint", &Rect64::MidPoint)
        .function("AsPath", &Rect64::AsPath)
        .function("ContainsPoint(point)", select_overload<bool(const Point<int64_t>&) const>(&Rect<int64_t>::Contains))
        .function("ContainsRect(rect)", select_overload<bool(const Rect<int64_t>&) const>(&Rect<int64_t>::Contains))
        .function("Scale(scale)", &Rect64::Scale)
        .function("IsEmpty", &Rect64::IsEmpty)
        .function("Intersects(rect)", &Rect64::Intersects)
        .function("Equals(other)", &Rect64::operator==);

        function("Ellipse64(center, radiusX, radiusY, steps)", select_overload<Path64(const Point64&, double, double, size_t)>(&Ellipse), allow_raw_pointers());
        function("EllipseFromRect64(rect, steps)", select_overload<Path64(const Rect64&, size_t)>(&Ellipse), allow_raw_pointers());

        // Translate64
        function("TranslatePath64(path, dx, dy)", select_overload<Path64(const Path64&, int64_t, int64_t)>(&TranslatePath), allow_raw_pointers());
        function("TranslatePaths64(paths, dx, dy)", select_overload<Paths64(const Paths64&, int64_t, int64_t)>(&TranslatePaths), allow_raw_pointers());

        // RectClip64
        function("RectClipPaths64(rect, paths)", select_overload<Paths64(const Rect64&, const Paths64&)>(&RectClip), allow_raw_pointers());
        function("RectClipPath64(rect, path)", select_overload<Paths64(const Rect64&, const Path64&)>(&RectClip), allow_raw_pointers());
        function("RectClipLinesPaths64(rect, lines)", select_overload<Paths64(const Rect64&, const Paths64&)>(&RectClipLines), allow_raw_pointers());
        function("RectClipLinesPath64(rect, line)", select_overload<Paths64(const Rect64&, const Path64&)>(&RectClipLines), allow_raw_pointers());

        // Minkowski
        function("MinkowskiSum64(pattern, path, isClosed)", select_overload<Paths64(const Path64&, const Path64&, bool)>(&MinkowskiSum), allow_raw_pointers());
        function("MinkowskiDiff64(pattern, path, isClosed)", select_overload<Paths64(const Path64&, const Path64&, bool)>(&MinkowskiDiff), allow_raw_pointers());

        // BooleanOps
        function("BooleanOp64(clipType, fillRule, subjects, clips)", select_overload<Paths64(ClipType, FillRule, const Paths64&, const Paths64&)>(&BooleanOp), allow_raw_pointers());
        function("BooleanOpOut64(clipType, fillRule, subjects, clips, solution)", select_overload<void(ClipType, FillRule, const Paths64&, const Paths64&, PolyTree64&)>(&BooleanOp), allow_raw_pointers());
        function("Intersect64(subjects, clips, fillRule)", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Intersect), allow_raw_pointers());
        function("Union64(subjects, clips, fillRule)", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Union), allow_raw_pointers());
        function("UnionSelf64(subjects, fillRule)", select_overload<Paths64(const Paths64&, FillRule)>(&Union), allow_raw_pointers());
        function("Difference64(subjects, clips, fillRule)", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Difference), allow_raw_pointers());
        function("Xor64(subjects, clips, fillRule)", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Xor), allow_raw_pointers());

        // Offset
        function("InflatePaths64(paths, delta, joinType, endType, miterLimit, arcTolerance)", select_overload<Paths64(const Paths64&, double, JoinType, EndType, double, double)>(&InflatePaths), allow_raw_pointers());

        // ClipperOffset64
        class_<ClipperOffset>("ClipperOffset64")
        .constructor<double, double, bool, bool>()
        .function("AddPath(path, joinType, endType)", &ClipperOffset::AddPath, allow_raw_pointers())
        .function("AddPaths(paths, joinType, endType)", &ClipperOffset::AddPaths, allow_raw_pointers())
        .function("Clear", &ClipperOffset::Clear)
        .function("Execute(delta, solution)", select_overload<void(double, Paths64&)>(&ClipperOffset::Execute), allow_raw_pointers())
        .function("SetDeltaCallback(cb)", &ClipperOffset_SetDeltaCallback, allow_raw_pointers())
        .function("ExecuteWithCallback(cb, solution)", &ClipperOffset_ExecuteCallback, allow_raw_pointers())
        .property("miterLimit", select_overload<double() const>(&ClipperOffset::MiterLimit), select_overload<void(double)>(&ClipperOffset::MiterLimit))
        .property("arcTolerance", select_overload<double() const>(&ClipperOffset::ArcTolerance), select_overload<void(double)>(&ClipperOffset::ArcTolerance))
        .property("preserveCollinear", select_overload<bool() const>(&ClipperOffset::PreserveCollinear), select_overload<void(bool)>(&ClipperOffset::PreserveCollinear))
        .property("reverseSolution", select_overload<bool() const>(&ClipperOffset::ReverseSolution), select_overload<void(bool)>(&ClipperOffset::ReverseSolution))
        .function("ErrorCode", &ClipperOffset::ErrorCode);

        // Simplify
        function("SimplifyPath64(path, epsilon, isClosedPath)", select_overload<Path64(const Path64&, double, bool)>(&SimplifyPath), allow_raw_pointers());
        function("SimplifyPaths64(paths, epsilon, isClosedPath)", select_overload<Paths64(const Paths64&, double, bool)>(&SimplifyPaths), allow_raw_pointers());
        function("TrimCollinear64(path, isOpenPath)", select_overload<Path64(const Path64&, bool)>(&TrimCollinear), allow_raw_pointers());

        // Triangulate
        function("Triangulate64(paths, useDelaunay)", &Triangulate64, allow_raw_pointers());

        // PolyPath
        class_<PolyPath>("PolyPath")
        .function("isHole", &PolyPath::IsHole);

        // PolyPath64
        class_<PolyPath64, base<PolyPath>>("PolyPath64")
        .constructor<>()
        .function("addChild(path)", &PolyPath64::AddChild, allow_raw_pointers())
        .function("clear", &PolyPath64::Clear)
        .function("count", &PolyPath64::Count)
        .function("polygon", &PolyPath64::Polygon)
        .function("area", &PolyPath64::Area)
        .function("child(index)", &PolyPath64::Child, allow_raw_pointers());

        // Clipper64
        class_<Clipper64, base<ClipperBase>>("Clipper64")
        .constructor<>()
        .function("AddSubject(subjects)", &Clipper64::AddSubject, allow_raw_pointers())
        .function("AddOpenSubject(openSubjects)", &Clipper64::AddOpenSubject, allow_raw_pointers())
        .function("AddClip(clips)", &Clipper64::AddClip, allow_raw_pointers())
        .function("Clear", &Clipper64::Clear)
        .function("ExecutePath(clipType, fillRule, closedPaths)", select_overload<bool(ClipType, FillRule, Paths64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePath(clipType, fillRule, closedPaths, openPaths)", select_overload<bool(ClipType, FillRule, Paths64&, Paths64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePoly(clipType, fillRule, polyTree)", select_overload<bool(ClipType, FillRule, PolyTree64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePoly(clipType, fillRule, polyTree, openPaths)", select_overload<bool(ClipType, FillRule, PolyTree64&, Paths64&)>(&Clipper64::Execute), allow_raw_pointers());

        function("CreateClipper64(preserveCollinear)", &CreateClipper64, allow_raw_pointers());

        // #############################
        // ###### 32 bit bindings ######
        // #############################

        // Point64 bindings (for now only support USINGZ=ON)
	#ifdef USINGZ
	class_<PointD>("PointD")
        .constructor<double, double, double>()
        .property("x", &PointD::x)
        .property("y", &PointD::y)
        .property("z", &PointD::z)
        .function("SetZ(z)", &PointD::SetZ);
	#endif

	// PathD
	class_<PathD>("PathD")
        .constructor<>()
        .function("size", &PathD::size)
        .function("clear", &PathD::clear)
        .function("resize(newSize)", select_overload<void(size_t)>(&PathD::resize))
        .function("push_back(point)", select_overload<void(const PointD&)>(&PathD::push_back))
        .function("get(index)", select_overload<PointD&(size_t)>(&PathD::operator[]), allow_raw_pointers())
#ifdef USINGZ
        .function("view", &PathD_view)
        .function("assign(coordinates)", &PathD_assign)
#endif
        ;

	// PathsD
	class_<PathsD>("PathsD")
		.constructor<>()
		.function("size", &PathsD::size)
		.function("clear", &PathsD::clear)
		.function("push_back(path)", select_overload<void(const PathD&)>(&PathsD::push_back))
		.function("get(index)", select_overload<PathD&(size_t)>(&PathsD::operator[]), allow_raw_pointers());

        // MiscD
        function("AreaPathD(path)", select_overload<double(const PathD&)>(&Area), allow_raw_pointers());
        function("AreaPathsD(paths)", select_overload<double(const PathsD&)>(&Area), allow_raw_pointers());
        function("IsPositiveD(poly)", select_overload<bool(const PathD&)>(&IsPositive), allow_raw_pointers());
        function("PointInPolygonD(point, polygon)", select_overload<PointInPolygonResult(const PointD&, const PathD&)>(&PointInPolygon), allow_raw_pointers());
        function("ReversePathD(path)", &ReversePath<double>, allow_raw_pointers());

        // GeometryD
        class_<RectD>("RectD")
        .constructor<>()
        .constructor<double, double, double, double>()
        .property("left", &RectD::left)
        .property("top", &RectD::top)
        .property("right", &RectD::right)
        .property("bottom", &RectD::bottom)
        .function("IsValid", &RectD::IsValid)
        .function("Width", select_overload<double() const>(&Rect<double>::Width))
        .function("Height", select_overload<double() const>(&Rect<double>::Height))
        .function("MidPoint", &RectD::MidPoint)
        .function("AsPath", &RectD::AsPath)
        .function("ContainsPoint(point)", select_overload<bool(const Point<double>&) const>(&Rect<double>::Contains))
        .function("ContainsRect(rect)", select_overload<bool(const Rect<double>&) const>(&Rect<double>::Contains))
        .function("Scale(scale)", &RectD::Scale)
        .function("IsEmpty", &RectD::IsEmpty)
        .function("Intersects(rect)", &RectD::Intersects)
        .function("Equals(other)", &RectD::operator==);

        function("EllipseD(center, radiusX, radiusY, steps)", select_overload<PathD(const PointD&, double, double, size_t)>(&Ellipse), allow_raw_pointers());
        function("EllipseFromRectD(rect, steps)", select_overload<PathD(const RectD&, size_t)>(&Ellipse), allow_raw_pointers());

        // TranslateD
        function("TranslatePathD(path, dx, dy)", select_overload<PathD(const PathD&, double, double)>(&TranslatePath), allow_raw_pointers());
        function("TranslatePathsD(paths, dx, dy)", select_overload<PathsD(const PathsD&, double, double)>(&TranslatePaths), allow_raw_pointers());

        // RectClipD
        function("RectClipPathsD(rect, paths, precision)", select_overload<PathsD(const RectD&, const PathsD&, int)>(&RectClip), allow_raw_pointers());
        function("RectClipPathD(rect, path, precision)", select_overload<PathsD(const RectD&, const PathD&, int)>(&RectClip), allow_raw_pointers());
        function("RectClipLinesPathsD(rect, lines, precision)", select_overload<PathsD(const RectD&, const PathsD&, int)>(&RectClipLines), allow_raw_pointers());
        function("RectClipLinesPathD(rect, line, precision)", select_overload<PathsD(const RectD&, const PathD&, int)>(&RectClipLines), allow_raw_pointers());

        // Minkowski
        function("MinkowskiSumD(pattern, path, isClosed, decimalPlaces)", select_overload<PathsD(const PathD&, const PathD&, bool, int)>(&MinkowskiSum), allow_raw_pointers());
        function("MinkowskiDiffD(pattern, path, isClosed, decimalPlaces)", select_overload<PathsD(const PathD&, const PathD&, bool, int)>(&MinkowskiDiff), allow_raw_pointers());

        // BooleanOps
        function("BooleanOpD(clipType, fillRule, subjects, clips, precision)", select_overload<PathsD(ClipType, FillRule, const PathsD&, const PathsD&, int)>(&BooleanOp), allow_raw_pointers());
        function("BooleanOpOutD(clipType, fillRule, subjects, clips, polyTree, precision)", select_overload<void(ClipType, FillRule, const PathsD&, const PathsD&, PolyTreeD&, int)>(&BooleanOp), allow_raw_pointers());
        function("IntersectD(subjects, clips, fillRule, decimalPrecision)", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Intersect), allow_raw_pointers());
        function("UnionD(subjects, clips, fillRule, decimalPrecision)", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Union), allow_raw_pointers());
        function("UnionSelfD(subjects, fillRule, precision)", select_overload<PathsD(const PathsD&, FillRule, int)>(&Union), allow_raw_pointers());
        function("DifferenceD(subjects, clips, fillRule, decimalPrecision)", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Difference), allow_raw_pointers());
        function("XorD(subjects, clips, fillRule, decimalPrecision)", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Xor), allow_raw_pointers());

        // Offset
        function("InflatePathsD(paths, delta, joinType, endType, miterLimit, precision, arcTolerance)", select_overload<PathsD(const PathsD&, double, JoinType, EndType, double, int, double)>(&InflatePaths), allow_raw_pointers());

        // Simplify
        function("SimplifyPathD(path, epsilon, isClosedPath)", select_overload<PathD(const PathD&, double, bool)>(&SimplifyPath), allow_raw_pointers());
        function("SimplifyPathsD(paths, epsilon, isClosedPath)", select_overload<PathsD(const PathsD&, double, bool)>(&SimplifyPaths), allow_raw_pointers());
        function("TrimCollinearD(path, precision, isOpenPath)", select_overload<PathD(const PathD&, int, bool)>(&TrimCollinear), allow_raw_pointers());

        // Triangulate
        function("TriangulateD(paths, decimalPlaces, useDelaunay)", &TriangulateD, allow_raw_pointers());

        // PolyPathD
        class_<PolyPathD, base<PolyPath>>("PolyPathD")
        .constructor<>()
        .function("addChild(path)", select_overload<PolyPathD*(const PathD&)>(&PolyPathD::AddChild), allow_raw_pointers())
        .function("clear", &PolyPathD::Clear)
        .function("count", &PolyPathD::Count)
        .function("polygon", &PolyPathD::Polygon)
        .function("area", &PolyPathD::Area)
        .function("child(index)", &PolyPathD::Child, allow_raw_pointers());

        // ClipperD
        class_<ClipperD, base<ClipperBase>>("ClipperD")
        .constructor<int>()
        .function("AddSubject(subjects)", &ClipperD::AddSubject, allow_raw_pointers())
        .function("AddOpenSubject(openSubjects)", &ClipperD::AddOpenSubject, allow_raw_pointers())
        .function("AddClip(clips)", &ClipperD::AddClip, allow_raw_pointers())
        .function("Clear", &ClipperD::Clear)
        .function("ExecutePath(clipType, fillRule, closedPaths)", select_overload<bool(ClipType, FillRule, PathsD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePath(clipType, fillRule, closedPaths, openPaths)", select_overload<bool(ClipType, FillRule, PathsD&, PathsD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePoly(clipType, fillRule, polyTree)", select_overload<bool(ClipType, FillRule, PolyTreeD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePoly(clipType, fillRule, polyTree, openPaths)", select_overload<bool(ClipType, FillRule, PolyTreeD&, PathsD&)>(&ClipperD::Execute), allow_raw_pointers());

        function("CreateClipperD(preserveCollinear)", &CreateClipperD, allow_raw_pointers());
}
