function PathDToPath64(pathD) {
	let path = new Module["Path64"]();
	for (let i = 0; i < pathD.size(); i++) {
		const p = pathD.get(i);

		const x = typeof p.x !== 'bigint' ? BigInt(Math.round(p.x)) : p.x;
		const y = typeof p.y !== 'bigint' ? BigInt(Math.round(p.y)) : p.y;
		const z = typeof p.z !== 'bigint' ? BigInt(Math.round(p.z)) : p.z;

		let point = new Module["Point64"](x,y,z);
		path["push_back"](point);
	}
	return path;
}

Module["PathDToPath64"] = PathDToPath64;

function Path64ToPathD(path64) {
	let path = new Module["PathD"]();
	for (let i = 0; i < path64.size(); i++) {
		const p = path64.get(i);
		let point = new Module["PointD"](Number(p.x), Number(p.y), Number(p.z));
		path["push_back"](point);
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
	}
	return paths;
}

Module["PathsDToPaths64"] = PathsDToPaths64;

