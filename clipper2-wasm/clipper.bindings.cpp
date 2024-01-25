#include "clipper2/clipper.core.h"
#include "clipper2/clipper.h"
#include <emscripten/bind.h>

using namespace emscripten;
using namespace Clipper2Lib;

template <typename T>
void ReversePath(Path<T>& path) {
    std::reverse(path.begin(), path.end());
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

EMSCRIPTEN_BINDINGS(clipper_module) {
        class_<ClipperBase>("ClipperBase")
        .function("Clear", &ClipperBase::Clear)
        .function("SetPreserveCollinear", select_overload<void(bool)>(&ClipperBase::PreserveCollinear))
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
        .function("SetZ", &Point64::SetZ);
	#endif

	// Path64
	class_<Path64>("Path64")
        .constructor<>()
        .function("size", &Path64::size)
        .function("clear", &Path64::clear)
        .function("push_back", select_overload<void(const Point64&)>(&Path64::push_back))
        .function("get", select_overload<Point64&(size_t)>(&Path64::operator[]), allow_raw_pointers());

	// Paths64
	class_<Paths64>("Paths64")
        .constructor<>()
        .function("size", &Paths64::size)
        .function("clear", &Paths64::clear)
        .function("push_back", select_overload<void(const Path64&)>(&Paths64::push_back))
        .function("get", select_overload<Path64&(size_t)>(&Paths64::operator[]), allow_raw_pointers());

        // Misc64
        function("AreaPath64", select_overload<double(const Path64&)>(&Area), allow_raw_pointers());
        function("AreaPaths64", select_overload<double(const Paths64&)>(&Area), allow_raw_pointers());
        function("IsPositive64", select_overload<bool(const Path64&)>(&IsPositive), allow_raw_pointers());
        function("PointInPolygon64", select_overload<PointInPolygonResult(const Point64&, const Path64&)>(&PointInPolygon), allow_raw_pointers());
        function("ReversePath64", &ReversePath<int64_t>, allow_raw_pointers());

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
        .function("ContainsPoint", select_overload<bool(const Point<int64_t>&) const>(&Rect<int64_t>::Contains))
        .function("ContainsRect", select_overload<bool(const Rect<int64_t>&) const>(&Rect<int64_t>::Contains))
        .function("Scale", &Rect64::Scale)
        .function("IsEmpty", &Rect64::IsEmpty)
        .function("Intersects", &Rect64::Intersects)
        .function("Equals", &Rect64::operator==);

        function("Ellipse64", select_overload<Path64(const Point64&, double, double, int)>(&Ellipse), allow_raw_pointers());
        function("EllipseFromRect64", select_overload<Path64(const Rect64&, int)>(&Ellipse), allow_raw_pointers());

        // Translate64
        function("TranslatePath64", select_overload<Path64(const Path64&, int64_t, int64_t)>(&TranslatePath), allow_raw_pointers());
        function("TranslatePaths64", select_overload<Paths64(const Paths64&, int64_t, int64_t)>(&TranslatePaths), allow_raw_pointers());

        // RectClip64
        function("RectClipPaths64", select_overload<Paths64(const Rect64&, const Paths64&)>(&RectClip), allow_raw_pointers());
        function("RectClipPath64", select_overload<Paths64(const Rect64&, const Path64&)>(&RectClip), allow_raw_pointers());
        function("RectClipLinesPaths64", select_overload<Paths64(const Rect64&, const Paths64&)>(&RectClipLines), allow_raw_pointers());
        function("RectClipLinesPath64", select_overload<Paths64(const Rect64&, const Path64&)>(&RectClipLines), allow_raw_pointers());

        // Minkowski
        function("MinkowskiSum64", select_overload<Paths64(const Path64&, const Path64&, bool)>(&MinkowskiSum), allow_raw_pointers());
        function("MinkowskiDiff64", select_overload<Paths64(const Path64&, const Path64&, bool)>(&MinkowskiDiff), allow_raw_pointers());

        // BooleanOps
        function("BooleanOp64", select_overload<Paths64(ClipType, FillRule, const Paths64&, const Paths64&)>(&BooleanOp), allow_raw_pointers());
        function("BooleanOpOut64", select_overload<void(ClipType, FillRule, const Paths64&, const Paths64&, PolyTree64&)>(&BooleanOp), allow_raw_pointers());
        function("Intersect64", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Intersect), allow_raw_pointers());
        function("Union64", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Union), allow_raw_pointers());
        function("UnionSelf64", select_overload<Paths64(const Paths64&, FillRule)>(&Union), allow_raw_pointers());
        function("Difference64", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Difference), allow_raw_pointers());
        function("Xor64", select_overload<Paths64(const Paths64&, const Paths64&, FillRule)>(&Xor), allow_raw_pointers());

        // Offset
        function("InflatePaths64", select_overload<Paths64(const Paths64&, double, JoinType, EndType, double, double)>(&InflatePaths), allow_raw_pointers());

        // Simplify
        function("SimplifyPath64", select_overload<Path64(const Path64&, double, bool)>(&SimplifyPath), allow_raw_pointers());
        function("SimplifyPaths64", select_overload<Paths64(const Paths64&, double, bool)>(&SimplifyPaths), allow_raw_pointers());
        function("TrimCollinear64", select_overload<Path64(const Path64&, bool)>(&TrimCollinear), allow_raw_pointers());

        // PolyPath64
        class_<PolyPath64>("PolyPath64")
        .constructor<>()
        .function("addChild", &PolyPath64::AddChild, allow_raw_pointers())
        .function("clear", &PolyPath64::Clear)
        .function("count", &PolyPath64::Count)
        .function("polygon", &PolyPath64::Polygon)
        .function("area", &PolyPath64::Area)
        .function("child", &PolyPath64::Child, allow_raw_pointers());

        // Clipper64
        class_<Clipper64, base<ClipperBase>>("Clipper64")
        .constructor<>()
        .function("AddSubject", &Clipper64::AddSubject, allow_raw_pointers())
        .function("AddOpenSubject", &Clipper64::AddOpenSubject, allow_raw_pointers())
        .function("AddClip", &Clipper64::AddClip, allow_raw_pointers())
        .function("Clear", &Clipper64::Clear)
        .function("ExecutePath", select_overload<bool(ClipType, FillRule, Paths64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePath", select_overload<bool(ClipType, FillRule, Paths64&, Paths64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePoly", select_overload<bool(ClipType, FillRule, PolyTree64&)>(&Clipper64::Execute), allow_raw_pointers())
        .function("ExecutePoly", select_overload<bool(ClipType, FillRule, PolyTree64&, Paths64&)>(&Clipper64::Execute), allow_raw_pointers());

        function("CreateClipper64", &CreateClipper64, allow_raw_pointers());

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
        .function("SetZ", &PointD::SetZ);
	#endif

	// PathD
	class_<PathD>("PathD")
        .constructor<>()
        .function("size", &PathD::size)
        .function("clear", &PathD::clear)
        .function("push_back", select_overload<void(const PointD&)>(&PathD::push_back))
        .function("get", select_overload<PointD&(size_t)>(&PathD::operator[]), allow_raw_pointers());

	// PathsD
	class_<PathsD>("PathsD")
		.constructor<>()
		.function("size", &PathsD::size)
		.function("clear", &PathsD::clear)
		.function("push_back", select_overload<void(const PathD&)>(&PathsD::push_back))
		.function("get", select_overload<PathD&(size_t)>(&PathsD::operator[]), allow_raw_pointers());

        // MiscD
        function("AreaPathD", select_overload<double(const PathD&)>(&Area), allow_raw_pointers());
        function("AreaPathsD", select_overload<double(const PathsD&)>(&Area), allow_raw_pointers());
        function("IsPositiveD", select_overload<bool(const PathD&)>(&IsPositive), allow_raw_pointers());
        function("PointInPolygonD", select_overload<PointInPolygonResult(const PointD&, const PathD&)>(&PointInPolygon), allow_raw_pointers());
        function("ReversePathD", &ReversePath<double>, allow_raw_pointers());

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
        .function("ContainsPoint", select_overload<bool(const Point<double>&) const>(&Rect<double>::Contains))
        .function("ContainsRect", select_overload<bool(const Rect<double>&) const>(&Rect<double>::Contains))
        .function("Scale", &RectD::Scale)
        .function("IsEmpty", &RectD::IsEmpty)
        .function("Intersects", &RectD::Intersects)
        .function("Equals", &RectD::operator==);

        function("EllipseD", select_overload<PathD(const PointD&, double, double, int)>(&Ellipse), allow_raw_pointers());
        function("EllipseFromRectD", select_overload<PathD(const RectD&, int)>(&Ellipse), allow_raw_pointers());

        // TranslateD
        function("TranslatePathD", select_overload<PathD(const PathD&, double, double)>(&TranslatePath), allow_raw_pointers());
        function("TranslatePathsD", select_overload<PathsD(const PathsD&, double, double)>(&TranslatePaths), allow_raw_pointers());

        // RectClipD
        function("RectClipPathsD", select_overload<PathsD(const RectD&, const PathsD&, int)>(&RectClip), allow_raw_pointers());
        function("RectClipPathD", select_overload<PathsD(const RectD&, const PathD&, int)>(&RectClip), allow_raw_pointers());
        function("RectClipLinesPathsD", select_overload<PathsD(const RectD&, const PathsD&, int)>(&RectClipLines), allow_raw_pointers());
        function("RectClipLinesPathD", select_overload<PathsD(const RectD&, const PathD&, int)>(&RectClipLines), allow_raw_pointers());

        // Minkowski
        function("MinkowskiSumD", select_overload<PathsD(const PathD&, const PathD&, bool, int)>(&MinkowskiSum), allow_raw_pointers());
        function("MinkowskiDiffD", select_overload<PathsD(const PathD&, const PathD&, bool, int)>(&MinkowskiDiff), allow_raw_pointers());

        // BooleanOps
        function("BooleanOpD", select_overload<PathsD(ClipType, FillRule, const PathsD&, const PathsD&, int)>(&BooleanOp), allow_raw_pointers());
        function("BooleanOpOutD", select_overload<void(ClipType, FillRule, const PathsD&, const PathsD&, PolyTreeD&, int)>(&BooleanOp), allow_raw_pointers());
        function("IntersectD", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Intersect), allow_raw_pointers());
        function("UnionD", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Union), allow_raw_pointers());
        function("UnionSelfD", select_overload<PathsD(const PathsD&, FillRule, int)>(&Union), allow_raw_pointers());
        function("DifferenceD", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Difference), allow_raw_pointers());
        function("XorD", select_overload<PathsD(const PathsD&, const PathsD&, FillRule, int)>(&Xor), allow_raw_pointers());

        // Offset
        function("InflatePathsD", select_overload<PathsD(const PathsD&, double, JoinType, EndType, double, int, double)>(&InflatePaths), allow_raw_pointers());

        // Simplify
        function("SimplifyPathD", select_overload<PathD(const PathD&, double, bool)>(&SimplifyPath), allow_raw_pointers());
        function("SimplifyPathsD", select_overload<PathsD(const PathsD&, double, bool)>(&SimplifyPaths), allow_raw_pointers());
        function("TrimCollinearD", select_overload<PathD(const PathD&, int, bool)>(&TrimCollinear), allow_raw_pointers());

        // PolyPathD
        class_<PolyPathD>("PolyPathD")
        .constructor<>()
        .function("addChild", select_overload<PolyPathD*(const PathD&)>(&PolyPathD::AddChild), allow_raw_pointers())
        .function("clear", &PolyPathD::Clear)
        .function("count", &PolyPathD::Count)
        .function("polygon", &PolyPathD::Polygon)
        .function("area", &PolyPathD::Area)
        .function("child", &PolyPathD::Child, allow_raw_pointers());

        // ClipperD
        class_<ClipperD, base<ClipperBase>>("ClipperD")
        .constructor<int>()
        .function("AddSubject", &ClipperD::AddSubject, allow_raw_pointers())
        .function("AddOpenSubject", &ClipperD::AddOpenSubject, allow_raw_pointers())
        .function("AddClip", &ClipperD::AddClip, allow_raw_pointers())
        .function("Clear", &ClipperD::Clear)
        .function("ExecutePath", select_overload<bool(ClipType, FillRule, PathsD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePath", select_overload<bool(ClipType, FillRule, PathsD&, PathsD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePoly", select_overload<bool(ClipType, FillRule, PolyTreeD&)>(&ClipperD::Execute), allow_raw_pointers())
        .function("ExecutePoly", select_overload<bool(ClipType, FillRule, PolyTreeD&, PathsD&)>(&ClipperD::Execute), allow_raw_pointers());

        function("CreateClipperD", &CreateClipperD, allow_raw_pointers());
}
