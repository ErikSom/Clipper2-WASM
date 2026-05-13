function MakePath64(intArray) {
	if(intArray.length % 2 != 0) {
		throw "MakePath64: intArray.length must be even";
	}
	const n = intArray.length / 2;
	const flat = new BigInt64Array(n * 3); // z defaults to 0n
	for (let i = 0, j = 0; i < intArray.length; i += 2, j += 3) {
		const a = intArray[i], b = intArray[i + 1];
		flat[j]     = typeof a === 'bigint' ? a : BigInt(a);
		flat[j + 1] = typeof b === 'bigint' ? b : BigInt(b);
	}

	let path = new Module["Path64"]();
	path.assign(flat);
	return path;
}
Module["MakePath64"] = MakePath64;

function MakePathZ64(intArray) {
	if(intArray.length % 3 != 0) {
		throw "MakePathZ64: intArray.length must be multiple of 3";
	}
	const flat = new BigInt64Array(intArray.length);
	for (let i = 0; i < intArray.length; i++) {
		const item = intArray[i];
		flat[i] = typeof item === 'bigint' ? item : BigInt(item);
	}

	let path = new Module["Path64"]();
	path.assign(flat);
	return path;
}
Module["MakePathZ64"] = MakePathZ64;

function MakePathD(intArray) {
	if(intArray.length % 2 != 0) {
		throw "MakePathD: intArray.length must be even";
	}
	const n = intArray.length / 2;
	const flat = new Float64Array(n * 3); // z defaults to 0
	for (let i = 0, j = 0; i < intArray.length; i += 2, j += 3) {
		flat[j]     = intArray[i];
		flat[j + 1] = intArray[i + 1];
	}

	let path = new Module["PathD"]();
	path.assign(flat);
	return path;
}
Module["MakePathD"] = MakePathD;

function MakePathZD(intArray) {
	if(intArray.length % 3 != 0) {
		throw "MakePathZD: intArray.length must be multiple of 3";
	}
	const flat = intArray instanceof Float64Array ? intArray : Float64Array.from(intArray);

	let path = new Module["PathD"]();
	path.assign(flat);
	return path;
}
Module["MakePathZD"] = MakePathZD;

function PathDToPath64(pathD) {
	const src = pathD.view(); // Float64Array, length 3N
	const dst = new BigInt64Array(src.length);
	for (let i = 0; i < src.length; i++) {
		dst[i] = BigInt(Math.round(src[i]));
	}
	let path = new Module["Path64"]();
	path.assign(dst);
	return path;
}

Module["PathDToPath64"] = PathDToPath64;

function Path64ToPathD(path64) {
	const src = path64.view(); // BigInt64Array, length 3N
	const dst = new Float64Array(src.length);
	for (let i = 0; i < src.length; i++) {
		dst[i] = Number(src[i]);
	}
	let path = new Module["PathD"]();
	path.assign(dst);
	return path;
}

Module["Path64ToPathD"] = Path64ToPathD;

function Paths64ToPathsD(paths64) {
	let paths = new Module["PathsD"]();
	for (let i = 0; i < paths64.size(); i++) {
		const path64 = paths64.get(i);
		let path = Path64ToPathD(path64);
		paths["push_back"](path);
		path.delete();
		path64.delete();
	}
	return paths;
}

Module["Paths64ToPathsD"] = Paths64ToPathsD;

function PathsDToPaths64(pathsD) {
	let paths = new Module["Paths64"]();
	for (let i = 0; i < pathsD.size(); i++) {
		const pathD = pathsD.get(i);
		let path = PathDToPath64(pathD);
		paths["push_back"](path);
		path.delete();
		pathD.delete();
	}
	return paths;
}

Module["PathsDToPaths64"] = PathsDToPaths64;

