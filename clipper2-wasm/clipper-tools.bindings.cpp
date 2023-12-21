#include "clipper2/clipper.core.h"
#include "clipper.svg.h"
#include "clipper.svg.utils.h"
#include <emscripten/bind.h>

using namespace emscripten;
using namespace Clipper2Lib;

EMSCRIPTEN_BINDINGS(clipper_module) {
    enum_<FillRule>("FillRule")
        .value("EvenOdd", FillRule::EvenOdd)
        .value("NonZero", FillRule::NonZero)
        .value("Positive", FillRule::Positive)
        .value("Negative", FillRule::Negative);

	class_<SvgReader>("SvgReader")
    .constructor<>()
		.function("LoadFromFile", &SvgReader::LoadFromFile)
		.function("Clear", &SvgReader::Clear)
		.function("GetPaths", &SvgReader::GetPaths);

	class_<SvgWriter>("SvgWriter")
        .constructor<>()
        .function("Clear", &SvgWriter::Clear)
        .function("FillRule", &SvgWriter::Fill_Rule)
        .function("SaveToFile", &SvgWriter::SaveToFile);

	// SvgAddSolution
	function("SvgAddSolution", select_overload<void(SvgWriter&, const PathsD&, FillRule, bool)>(&SvgAddSolution));

	#ifdef USINGZ
	class_<PointD>("PointD")
		.constructor<double, double, double>()
		.property("x", &PointD::x)
		.property("y", &PointD::y)
		.property("z", &PointD::z)
		.function("SetZ", &PointD::SetZ);
	#else
	class_<PointD>("PointD")
		.constructor<double, double>()
		.property("x", &PointD::x)
		.property("y", &PointD::y);
	#endif

	class_<PathD>("PathD")
		.constructor<>()
		.function("size", &PathD::size)
		.function("clear", &PathD::clear)
		.function("push_back", select_overload<void(const PointD&)>(&PathD::push_back))
		.function("get", select_overload<PointD&(size_t)>(&PathD::operator[]), allow_raw_pointers());

	class_<PathsD>("PathsD")
		.constructor<>()
		.function("size", &PathsD::size)
		.function("clear", &PathsD::clear)
		.function("push_back", select_overload<void(const PathD&)>(&PathsD::push_back))
		.function("get", select_overload<PathD&(size_t)>(&PathsD::operator[]), allow_raw_pointers());

	// Point64 bindings (for now only support USINGZ=ON)
	#ifdef USINGZ
	class_<Point64>("Point64")
		.constructor<int64_t, int64_t, int64_t>()
		.property("x", &Point64::x)
		.property("y", &Point64::y)
		.property("z", &Point64::z)
		.function("SetZ", &Point64::SetZ);
	#else
	class_<Point64>("Point64")
		.constructor<int64_t, int64_t>()
		.property("x", &Point64::x)
		.property("y", &Point64::y);
	#endif
}
