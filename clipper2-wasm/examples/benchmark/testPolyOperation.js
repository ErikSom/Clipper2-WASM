function testPolyOperationClipper1(
	lib,
	clipType,
	subjectFillType,
	subjectInput,
	clipInput
) {
	const data = {
		clipType,
		subjectInputs: [{ data: subjectInput, closed: true }],
		clipInputs: [{ data: clipInput }],
		subjectFillType: subjectFillType,
	};

	lib.clipToPaths(data);
}

let out;
function initPolyOperationClipper2(lib) {
	out = new lib.PathsD();
}

function testPolyOperationClipper2(
	lib,
	clipType,
	subjectFillType,
	subject,
	clip
) {
	const clipper2 = new lib.CreateClipperD(false);
	clipper2.AddSubject(subject);
	clipper2.AddClip(clip);
	clipper2.ExecutePath(clipType, subjectFillType, out);
	clipper2.delete();
}
