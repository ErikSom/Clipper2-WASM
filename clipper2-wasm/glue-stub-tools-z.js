function PathDToPath64(pathD) {
	const src = pathD.view();
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
	let path = new Module["PathD"]();
	for (let i = 0; i < path64.size(); i++) {
		const p = path64.get(i);
		let point = new Module["PointD"](Number(p.x), Number(p.y), Number(p.z));
		path["push_back"](point);
		point.delete();
		p.delete();
	}
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

