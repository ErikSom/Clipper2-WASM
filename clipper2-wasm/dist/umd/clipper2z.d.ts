export interface ClipperBase {
  Clear(): void;
  Clear(): void;
  Clear(): void;
  SetPreserveCollinear(_0: boolean): void;
  GetPreserveCollinear(): boolean;
  delete(): void;
}

export interface FillRuleValue<T extends number> {
  value: T;
}
export type FillRule = FillRuleValue<0>|FillRuleValue<1>|FillRuleValue<2>|FillRuleValue<3>;

export interface ClipTypeValue<T extends number> {
  value: T;
}
export type ClipType = ClipTypeValue<1>|ClipTypeValue<2>|ClipTypeValue<3>|ClipTypeValue<4>;

export interface PathTypeValue<T extends number> {
  value: T;
}
export type PathType = PathTypeValue<0>|PathTypeValue<1>;

export interface JoinTypeValue<T extends number> {
  value: T;
}
export type JoinType = JoinTypeValue<0>|JoinTypeValue<2>|JoinTypeValue<3>;

export interface EndTypeValue<T extends number> {
  value: T;
}
export type EndType = EndTypeValue<0>|EndTypeValue<1>|EndTypeValue<2>|EndTypeValue<3>|EndTypeValue<4>;

export interface PointInPolygonResultValue<T extends number> {
  value: T;
}
export type PointInPolygonResult = PointInPolygonResultValue<0>|PointInPolygonResultValue<1>|PointInPolygonResultValue<2>;

export interface Point64 {
  x: bigint;
  y: bigint;
  z: bigint;
  SetZ(_0: bigint): void;
  delete(): void;
}

export interface Path64 {
  clear(): void;
  push_back(_0: Point64): void;
  size(): number;
  get(_0: number): Point64;
  delete(): void;
}

export interface Paths64 {
  clear(): void;
  push_back(_0: Path64): void;
  size(): number;
  get(_0: number): Path64;
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
  ContainsPoint(_0: Point64): boolean;
  ContainsRect(_0: Rect64): boolean;
  IsEmpty(): boolean;
  Intersects(_0: Rect64): boolean;
  Equals(_0: Rect64): boolean;
  Width(): bigint;
  Height(): bigint;
  Scale(_0: number): void;
  delete(): void;
}

export interface PolyPath64 {
  addChild(_0: Path64): PolyPath64;
  polygon(): Path64;
  clear(): void;
  count(): number;
  child(_0: number): PolyPath64;
  area(): number;
  delete(): void;
}

export interface Clipper64 extends ClipperBase {
  AddSubject(_0: Paths64): void;
  AddOpenSubject(_0: Paths64): void;
  AddClip(_0: Paths64): void;
  ExecutePath(_0: ClipType, _1: FillRule, _2: Paths64): boolean;
  ExecutePath(_0: ClipType, _1: FillRule, _2: Paths64, _3: Paths64): boolean;
  ExecutePoly(_0: ClipType, _1: FillRule, _2: PolyPath64): boolean;
  ExecutePoly(_0: ClipType, _1: FillRule, _2: PolyPath64, _3: Paths64): boolean;
  delete(): void;
}

export interface PointD {
  z: bigint;
  x: number;
  y: number;
  SetZ(_0: bigint): void;
  delete(): void;
}

export interface PathD {
  clear(): void;
  push_back(_0: PointD): void;
  size(): number;
  get(_0: number): PointD;
  delete(): void;
}

export interface PathsD {
  clear(): void;
  push_back(_0: PathD): void;
  size(): number;
  get(_0: number): PathD;
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
  ContainsPoint(_0: PointD): boolean;
  ContainsRect(_0: RectD): boolean;
  IsEmpty(): boolean;
  Intersects(_0: RectD): boolean;
  Equals(_0: RectD): boolean;
  Width(): number;
  Height(): number;
  Scale(_0: number): void;
  delete(): void;
}

export interface PolyPathD {
  addChild(_0: PathD): PolyPathD;
  polygon(): PathD;
  clear(): void;
  count(): number;
  child(_0: number): PolyPathD;
  area(): number;
  delete(): void;
}

export interface ClipperD extends ClipperBase {
  AddSubject(_0: PathsD): void;
  AddOpenSubject(_0: PathsD): void;
  AddClip(_0: PathsD): void;
  ExecutePath(_0: ClipType, _1: FillRule, _2: PathsD): boolean;
  ExecutePath(_0: ClipType, _1: FillRule, _2: PathsD, _3: PathsD): boolean;
  ExecutePoly(_0: ClipType, _1: FillRule, _2: PolyPathD): boolean;
  ExecutePoly(_0: ClipType, _1: FillRule, _2: PolyPathD, _3: PathsD): boolean;
  delete(): void;
}

export interface MainModule {
  ClipperBase: {};
  FillRule: {EvenOdd: FillRuleValue<0>, NonZero: FillRuleValue<1>, Positive: FillRuleValue<2>, Negative: FillRuleValue<3>};
  ClipType: {Intersection: ClipTypeValue<1>, Union: ClipTypeValue<2>, Difference: ClipTypeValue<3>, Xor: ClipTypeValue<4>};
  PathType: {Subject: PathTypeValue<0>, Clip: PathTypeValue<1>};
  JoinType: {Square: JoinTypeValue<0>, Round: JoinTypeValue<2>, Miter: JoinTypeValue<3>};
  EndType: {Polygon: EndTypeValue<0>, Joined: EndTypeValue<1>, Butt: EndTypeValue<2>, Square: EndTypeValue<3>, Round: EndTypeValue<4>};
  PointInPolygonResult: {IsOn: PointInPolygonResultValue<0>, IsInside: PointInPolygonResultValue<1>, IsOutside: PointInPolygonResultValue<2>};
  Point64: {new(_0: bigint, _1: bigint, _2: bigint): Point64};
  Path64: {new(): Path64};
  Paths64: {new(): Paths64};
  PointInPolygon64(_0: Point64, _1: Path64): PointInPolygonResult;
  Rect64: {new(): Rect64; new(_0: bigint, _1: bigint, _2: bigint, _3: bigint): Rect64};
  RectClipPaths64(_0: Rect64, _1: Paths64): Paths64;
  RectClipPath64(_0: Rect64, _1: Path64): Paths64;
  RectClipLinesPaths64(_0: Rect64, _1: Paths64): Paths64;
  RectClipLinesPath64(_0: Rect64, _1: Path64): Paths64;
  BooleanOp64(_0: ClipType, _1: FillRule, _2: Paths64, _3: Paths64): Paths64;
  Intersect64(_0: Paths64, _1: Paths64, _2: FillRule): Paths64;
  Union64(_0: Paths64, _1: Paths64, _2: FillRule): Paths64;
  UnionSelf64(_0: Paths64, _1: FillRule): Paths64;
  Difference64(_0: Paths64, _1: Paths64, _2: FillRule): Paths64;
  Xor64(_0: Paths64, _1: Paths64, _2: FillRule): Paths64;
  PolyPath64: {new(): PolyPath64};
  Clipper64: {new(): Clipper64};
  PointD: {new(_0: number, _1: number, _2: number): PointD};
  PathD: {new(): PathD};
  PathsD: {new(): PathsD};
  PointInPolygonD(_0: PointD, _1: PathD): PointInPolygonResult;
  RectD: {new(): RectD; new(_0: number, _1: number, _2: number, _3: number): RectD};
  PolyPathD: {new(): PolyPathD};
  ClipperD: {new(): ClipperD};
  ReversePath64(_0: Path64): void;
  BooleanOpOut64(_0: ClipType, _1: FillRule, _2: Paths64, _3: Paths64, _4: PolyPath64): void;
  ReversePathD(_0: PathD): void;
  IsPositive64(_0: Path64): boolean;
  MinkowskiSum64(_0: Path64, _1: Path64, _2: boolean): Paths64;
  MinkowskiDiff64(_0: Path64, _1: Path64, _2: boolean): Paths64;
  TrimCollinear64(_0: Path64, _1: boolean): Path64;
  CreateClipper64(_0: boolean): Clipper64;
  IsPositiveD(_0: PathD): boolean;
  CreateClipperD(_0: boolean): ClipperD;
  EllipseFromRect64(_0: Rect64, _1: number): Path64;
  EllipseFromRectD(_0: RectD, _1: number): PathD;
  RectClipPathsD(_0: RectD, _1: PathsD, _2: number): PathsD;
  RectClipPathD(_0: RectD, _1: PathD, _2: number): PathsD;
  RectClipLinesPathsD(_0: RectD, _1: PathsD, _2: number): PathsD;
  RectClipLinesPathD(_0: RectD, _1: PathD, _2: number): PathsD;
  MinkowskiSumD(_0: PathD, _1: PathD, _2: boolean, _3: number): PathsD;
  MinkowskiDiffD(_0: PathD, _1: PathD, _2: boolean, _3: number): PathsD;
  BooleanOpD(_0: ClipType, _1: FillRule, _2: PathsD, _3: PathsD, _4: number): PathsD;
  BooleanOpOutD(_0: ClipType, _1: FillRule, _2: PathsD, _3: PathsD, _4: PolyPathD, _5: number): void;
  IntersectD(_0: PathsD, _1: PathsD, _2: FillRule, _3: number): PathsD;
  UnionD(_0: PathsD, _1: PathsD, _2: FillRule, _3: number): PathsD;
  UnionSelfD(_0: PathsD, _1: FillRule, _2: number): PathsD;
  DifferenceD(_0: PathsD, _1: PathsD, _2: FillRule, _3: number): PathsD;
  XorD(_0: PathsD, _1: PathsD, _2: FillRule, _3: number): PathsD;
  TrimCollinearD(_0: PathD, _1: number, _2: boolean): PathD;
  TranslatePath64(_0: Path64, _1: bigint, _2: bigint): Path64;
  TranslatePaths64(_0: Paths64, _1: bigint, _2: bigint): Paths64;
  AreaPath64(_0: Path64): number;
  AreaPaths64(_0: Paths64): number;
  Ellipse64(_0: Point64, _1: number, _2: number, _3: number): Path64;
  InflatePaths64(_0: Paths64, _1: number, _2: JoinType, _3: EndType, _4: number, _5: number): Paths64;
  SimplifyPath64(_0: Path64, _1: number, _2: boolean): Path64;
  SimplifyPaths64(_0: Paths64, _1: number, _2: boolean): Paths64;
  AreaPathD(_0: PathD): number;
  AreaPathsD(_0: PathsD): number;
  EllipseD(_0: PointD, _1: number, _2: number, _3: number): PathD;
  TranslatePathD(_0: PathD, _1: number, _2: number): PathD;
  TranslatePathsD(_0: PathsD, _1: number, _2: number): PathsD;
  InflatePathsD(_0: PathsD, _1: number, _2: JoinType, _3: EndType, _4: number, _5: number, _6: number): PathsD;
  SimplifyPathD(_0: PathD, _1: number, _2: boolean): PathD;
  SimplifyPathsD(_0: PathsD, _1: number, _2: boolean): PathsD;
}
