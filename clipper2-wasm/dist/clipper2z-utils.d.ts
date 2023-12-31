/// <reference types="emscripten" />
export interface Clipper2ZUtilsFactoryFunction extends EmscriptenModuleFactory<MainModule & EmscriptenModule> { }

export interface FillRuleValue<T extends number> {
  value: T;
}
export type FillRule = FillRuleValue<0>|FillRuleValue<1>|FillRuleValue<2>|FillRuleValue<3>;

export interface SvgReader {
  GetPaths(): PathsD;
  Clear(): void;
  LoadFromFile(_0: ArrayBuffer|Uint8Array|Uint8ClampedArray|Int8Array|string): boolean;
  delete(): void;
}

export interface SvgWriter {
  FillRule(): FillRule;
  Clear(): void;
  SaveToFile(_0: ArrayBuffer|Uint8Array|Uint8ClampedArray|Int8Array|string, _1: number, _2: number, _3: number): boolean;
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

export interface PathsD {
  clear(): void;
  push_back(_0: PathD): void;
  size(): number;
  get(_0: number): PathD;
  delete(): void;
}

export interface Point64 {
  x: bigint;
  y: bigint;
  z: bigint;
  SetZ(_0: bigint): void;
  delete(): void;
}

export interface MainModule {
  FillRule: {EvenOdd: FillRuleValue<0>, NonZero: FillRuleValue<1>, Positive: FillRuleValue<2>, Negative: FillRuleValue<3>};
  SvgReader: {new(): SvgReader};
  SvgWriter: {new(): SvgWriter};
  PointD: {new(_0: number, _1: number, _2: number): PointD};
  PathD: {new(): PathD};
  PathsD: {new(): PathsD};
  Point64: {new(_0: bigint, _1: bigint, _2: bigint): Point64};
  SvgAddSolution(_0: SvgWriter, _1: PathsD, _2: FillRule, _3: boolean): void;
  PathDToPath64(pathD: PathD): Path64;
  Path64ToPathD(path64: Path64): PathD;
  Paths64ToPathsD(paths64: Paths64): PathsD;
  PathsDToPaths64(pathsD: PathsD): Paths64;
}
