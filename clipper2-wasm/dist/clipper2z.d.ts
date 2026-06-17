/// <reference types="emscripten" />
export interface Clipper2ZFactoryFunction extends EmscriptenModuleFactory<MainModule & EmscriptenModule> { }

export interface ClipperBase {
  Clear(): void;
  SetPreserveCollinear(preserveCollinear: boolean): void;
  GetPreserveCollinear(): boolean;
  delete(): void;
}

export interface FillRuleValue<T extends number> {
  value: T;
}
export type FillRule = FillRuleValue<0> | FillRuleValue<1> | FillRuleValue<2> | FillRuleValue<3>;

export interface ClipTypeValue<T extends number> {
  value: T;
}
export type ClipType = ClipTypeValue<1> | ClipTypeValue<2> | ClipTypeValue<3> | ClipTypeValue<4>;

export interface PathTypeValue<T extends number> {
  value: T;
}
export type PathType = PathTypeValue<0> | PathTypeValue<1>;

export interface JoinTypeValue<T extends number> {
  value: T;
}
export type JoinType = JoinTypeValue<0> | JoinTypeValue<2> | JoinTypeValue<3>;

export interface EndTypeValue<T extends number> {
  value: T;
}
export type EndType = EndTypeValue<0> | EndTypeValue<1> | EndTypeValue<2> | EndTypeValue<3> | EndTypeValue<4>;

export interface PointInPolygonResultValue<T extends number> {
  value: T;
}
export type PointInPolygonResult = PointInPolygonResultValue<0> | PointInPolygonResultValue<1> | PointInPolygonResultValue<2>;

export interface TriangulateResultValue<T extends number> {
  value: T;
}
export type TriangulateResult = TriangulateResultValue<0> | TriangulateResultValue<1> | TriangulateResultValue<2> | TriangulateResultValue<3>;

export interface TriangulateResult64 {
  result: TriangulateResult;
  solution: Paths64;
}

export interface TriangulateResultD {
  result: TriangulateResult;
  solution: PathsD;
}

export interface Point64 {
  x: bigint;
  y: bigint;
  z: bigint;
  SetZ(z: bigint): void;
  delete(): void;
}

export interface Path64 {
  clear(): void;
  push_back(point: Point64): void;
  size(): number;
  get(index: number): Point64;
  resize(newSize: number): void;
  view(): BigInt64Array;
  assign(coordinates: BigInt64Array): void;
  delete(): void;
}

export interface Paths64 {
  clear(): void;
  push_back(path: Path64): void;
  size(): number;
  get(index: number): Path64;
  delete(): void;
}

export interface Rect64 {
  left: bigint;
  top: bigint;
  right: bigint;
  bottom: bigint;
  MidPoint(): Point64;
  AsPath(): Path64;
  IsValid(): boolean;
  ContainsPoint(point: Point64): boolean;
  ContainsRect(rect: Rect64): boolean;
  IsEmpty(): boolean;
  Intersects(rect: Rect64): boolean;
  Equals(other: Rect64): boolean;
  Width(): bigint;
  Height(): bigint;
  Scale(scale: number): void;
  delete(): void;
}

export interface PolyPath {
  isHole(): boolean;
}

export interface PolyPath64 extends PolyPath {
  addChild(path: Path64): PolyPath64;
  polygon(): Path64;
  clear(): void;
  count(): number;
  child(index: number): PolyPath64;
  area(): number;
  delete(): void;
}

export interface Clipper64 extends ClipperBase {
  AddSubject(subjects: Paths64): void;
  AddOpenSubject(openSubjects: Paths64): void;
  AddClip(clips: Paths64): void;
  ExecutePath(clipType: ClipType, fillRule: FillRule, closedPaths: Paths64): boolean;
  ExecutePath(clipType: ClipType, fillRule: FillRule, closedPaths: Paths64, openPaths: Paths64): boolean;
  ExecutePoly(clipType: ClipType, fillRule: FillRule, polyTree: PolyPath64): boolean;
  ExecutePoly(clipType: ClipType, fillRule: FillRule, polyTree: PolyPath64, openPaths: Paths64): boolean;
  delete(): void;
}

export interface PointD {
  z: bigint;
  x: number;
  y: number;
  SetZ(z: bigint): void;
  delete(): void;
}

export interface PathD {
  clear(): void;
  push_back(point: PointD): void;
  size(): number;
  get(index: number): PointD;
  resize(newSize: number): void;
  view(): Float64Array;
  assign(coordinates: Float64Array): void;
  delete(): void;
}

export interface PathsD {
  clear(): void;
  push_back(path: PathD): void;
  size(): number;
  get(index: number): PathD;
  delete(): void;
}

export interface RectD {
  left: number;
  top: number;
  right: number;
  bottom: number;
  MidPoint(): PointD;
  AsPath(): PathD;
  IsValid(): boolean;
  ContainsPoint(point: PointD): boolean;
  ContainsRect(rect: RectD): boolean;
  IsEmpty(): boolean;
  Intersects(rect: RectD): boolean;
  Equals(other: RectD): boolean;
  Width(): number;
  Height(): number;
  Scale(scale: number): void;
  delete(): void;
}

export interface PolyPathD extends PolyPath {
  addChild(path: PathD): PolyPathD;
  polygon(): PathD;
  clear(): void;
  count(): number;
  child(index: number): PolyPathD;
  area(): number;
  delete(): void;
}

export interface ClipperD extends ClipperBase {
  AddSubject(subjects: PathsD): void;
  AddOpenSubject(openSubjects: PathsD): void;
  AddClip(clips: PathsD): void;
  ExecutePath(clipType: ClipType, fillRule: FillRule, closedPaths: PathsD): boolean;
  ExecutePath(clipType: ClipType, fillRule: FillRule, closedPaths: PathsD, openPaths: PathsD): boolean;
  ExecutePoly(clipType: ClipType, fillRule: FillRule, polyTree: PolyPathD): boolean;
  ExecutePoly(clipType: ClipType, fillRule: FillRule, polyTree: PolyPathD, openPaths: PathsD): boolean;
  delete(): void;
}

export interface ClipperOffset64 {
  AddPath(path: Path64, joinType: JoinType, endType: EndType): void;
  AddPaths(paths: Paths64, joinType: JoinType, endType: EndType): void;
  Clear(): void;
  Execute(delta: number, solution: Paths64): void;
  ExecuteWithCallback(cb: (path: Path64, path_normals: PathD, curr_idx: number, prev_idx: number) => number, solution: Paths64): void;
  SetDeltaCallback(cb: (path: Path64, path_normals: PathD, curr_idx: number, prev_idx: number) => number): void;
  miterLimit: number;
  arcTolerance: number;
  preserveCollinear: boolean;
  reverseSolution: boolean;
  ErrorCode(): number;
  delete(): void;
}

export interface MainModule {
  ClipperBase: {};
  FillRule: { EvenOdd: FillRuleValue<0>, NonZero: FillRuleValue<1>, Positive: FillRuleValue<2>, Negative: FillRuleValue<3> };
  ClipType: { Intersection: ClipTypeValue<1>, Union: ClipTypeValue<2>, Difference: ClipTypeValue<3>, Xor: ClipTypeValue<4> };
  PathType: { Subject: PathTypeValue<0>, Clip: PathTypeValue<1> };
  JoinType: { Square: JoinTypeValue<0>, Round: JoinTypeValue<2>, Miter: JoinTypeValue<3> };
  EndType: { Polygon: EndTypeValue<0>, Joined: EndTypeValue<1>, Butt: EndTypeValue<2>, Square: EndTypeValue<3>, Round: EndTypeValue<4> };
  PointInPolygonResult: { IsOn: PointInPolygonResultValue<0>, IsInside: PointInPolygonResultValue<1>, IsOutside: PointInPolygonResultValue<2> };
  TriangulateResult: { Success: TriangulateResultValue<0>, Fail: TriangulateResultValue<1>, NoPolygons: TriangulateResultValue<2>, PathsIntersect: TriangulateResultValue<3> };
  Point64: { new(x: bigint, y: bigint, z: bigint): Point64 };
  Path64: { new(): Path64 };
  Paths64: { new(): Paths64 };
  PointInPolygon64(point: Point64, polygon: Path64): PointInPolygonResult;
  Rect64: { new(): Rect64; new(left: bigint, top: bigint, right: bigint, bottom: bigint): Rect64 };
  RectClipPaths64(rect: Rect64, paths: Paths64): Paths64;
  RectClipPath64(rect: Rect64, path: Path64): Paths64;
  RectClipLinesPaths64(rect: Rect64, lines: Paths64): Paths64;
  RectClipLinesPath64(rect: Rect64, line: Path64): Paths64;
  BooleanOp64(clipType: ClipType, fillRule: FillRule, subjects: Paths64, clips: Paths64): Paths64;
  Intersect64(subjects: Paths64, clips: Paths64, fillRule: FillRule): Paths64;
  Union64(subjects: Paths64, clips: Paths64, fillRule: FillRule): Paths64;
  UnionSelf64(subjects: Paths64, fillRule: FillRule): Paths64;
  Difference64(subjects: Paths64, clips: Paths64, fillRule: FillRule): Paths64;
  Xor64(subjects: Paths64, clips: Paths64, fillRule: FillRule): Paths64;
  PolyPath64: { new(): PolyPath64 };
  Clipper64: { new(): Clipper64 };
  PointD: { new(x: number, y: number, z: number): PointD };
  PathD: { new(): PathD };
  PathsD: { new(): PathsD };
  PointInPolygonD(point: PointD, polygon: PathD): PointInPolygonResult;
  RectD: { new(): RectD; new(left: number, top: number, right: number, bottom: number): RectD };
  PolyPathD: { new(): PolyPathD };
  ClipperD: { new(precision: number): ClipperD };
  ReversePath64(path: Path64): void;
  BooleanOpOut64(clipType: ClipType, fillRule: FillRule, subjects: Paths64, clips: Paths64, solution: PolyPath64): void;
  ReversePathD(path: PathD): void;
  IsPositive64(poly: Path64): boolean;
  MinkowskiSum64(pattern: Path64, path: Path64, isClosed: boolean): Paths64;
  MinkowskiDiff64(pattern: Path64, path: Path64, isClosed: boolean): Paths64;
  TrimCollinear64(path: Path64, isOpenPath: boolean): Path64;
  CreateClipper64(preserveCollinear: boolean): Clipper64;
  IsPositiveD(poly: PathD): boolean;
  CreateClipperD(preserveCollinear: boolean): ClipperD;
  ClipperOffset64: { new(miterLimit?: number, arcTolerance?: number, preserveCollinear?: boolean, reverseSolution?: boolean): ClipperOffset64 };
  EllipseFromRect64(rect: Rect64, steps: number): Path64;
  EllipseFromRectD(rect: RectD, steps: number): PathD;
  RectClipPathsD(rect: RectD, paths: PathsD, precision: number): PathsD;
  RectClipPathD(rect: RectD, path: PathD, precision: number): PathsD;
  RectClipLinesPathsD(rect: RectD, lines: PathsD, precision: number): PathsD;
  RectClipLinesPathD(rect: RectD, line: PathD, precision: number): PathsD;
  MinkowskiSumD(pattern: PathD, path: PathD, isClosed: boolean, decimalPlaces: number): PathsD;
  MinkowskiDiffD(pattern: PathD, path: PathD, isClosed: boolean, decimalPlaces: number): PathsD;
  BooleanOpD(clipType: ClipType, fillRule: FillRule, subjects: PathsD, clips: PathsD, precision: number): PathsD;
  BooleanOpOutD(clipType: ClipType, fillRule: FillRule, subjects: PathsD, clips: PathsD, polyTree: PolyPathD, precision: number): void;
  IntersectD(subjects: PathsD, clips: PathsD, fillRule: FillRule, decimalPrecision: number): PathsD;
  UnionD(subjects: PathsD, clips: PathsD, fillRule: FillRule, decimalPrecision: number): PathsD;
  UnionSelfD(subjects: PathsD, fillRule: FillRule, precision: number): PathsD;
  DifferenceD(subjects: PathsD, clips: PathsD, fillRule: FillRule, decimalPrecision: number): PathsD;
  XorD(subjects: PathsD, clips: PathsD, fillRule: FillRule, decimalPrecision: number): PathsD;
  TrimCollinearD(path: PathD, precision: number, isOpenPath: boolean): PathD;
  TranslatePath64(path: Path64, dx: bigint, dy: bigint): Path64;
  TranslatePaths64(paths: Paths64, dx: bigint, dy: bigint): Paths64;
  AreaPath64(path: Path64): number;
  AreaPaths64(paths: Paths64): number;
  Ellipse64(center: Point64, radiusX: number, radiusY: number, steps: number): Path64;
  InflatePaths64(paths: Paths64, delta: number, joinType: JoinType, endType: EndType, miterLimit: number, arcTolerance: number): Paths64;
  SimplifyPath64(path: Path64, epsilon: number, isClosedPath: boolean): Path64;
  SimplifyPaths64(paths: Paths64, epsilon: number, isClosedPath: boolean): Paths64;
  Triangulate64(paths: Paths64, useDelaunay: boolean): TriangulateResult64;
  TriangulateD(paths: PathsD, decimalPlaces: number, useDelaunay: boolean): TriangulateResultD;
  AreaPathD(path: PathD): number;
  AreaPathsD(paths: PathsD): number;
  EllipseD(center: PointD, radiusX: number, radiusY: number, steps: number): PathD;
  TranslatePathD(path: PathD, dx: number, dy: number): PathD;
  TranslatePathsD(paths: PathsD, dx: number, dy: number): PathsD;
  InflatePathsD(paths: PathsD, delta: number, joinType: JoinType, endType: EndType, miterLimit: number, precision: number, arcTolerance: number): PathsD;
  SimplifyPathD(path: PathD, epsilon: number, isClosedPath: boolean): PathD;
  SimplifyPathsD(paths: PathsD, epsilon: number, isClosedPath: boolean): PathsD;
  MakePath64(intArray: Array<number | bigint>): Path64;
  MakePathZ64(intArray: Array<number | bigint>): Path64;
  MakePathD(intArray: number[]): PathD;
  MakePathZD(intArray: number[]): PathD;
  PathDToPath64(pathD: PathD): Path64;
  Path64ToPathD(path64: Path64): PathD;
  Paths64ToPathsD(paths64: Paths64): PathsD;
  PathsDToPaths64(pathsD: PathsD): Paths64;
}
