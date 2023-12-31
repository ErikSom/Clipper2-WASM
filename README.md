[![npm version](https://badge.fury.io/js/clipper2-wasm.svg)](https://badge.fury.io/js/clipper2-wasm)
# Clipper2 WASM

The <b>Clipper2</b> library performs **intersection**, **union**, **difference** and **XOR** boolean operations on both simple and complex polygons. It also performs polygon offsetting.

## Documentation:
For Clipper2 documentation please see the [Extensive HTML documentation](http://www.angusj.com/clipper2/Docs/Overview.htm)

## Live examples:
- [Basic](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/basic.html)
- [SVG-Tools](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/svg-tools.html)
- [Rect Clip](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/rectclip.html)
- [Offset](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/offset.html)
- [Minkowski](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/minkowski.html)
- [Rect Clip Lines](https://eriksom.github.io/Clipper2-WASM/clipper2-wasm/examples/es/rectclip-lines.html)

## Download lib
ES6: https://github.com/ErikSom/Clipper2-WASM/tree/main/CPP/clipper2-wasm/dist/es/

UMD: https://github.com/ErikSom/Clipper2-WASM/tree/main/CPP/clipper2-wasm/dist/umd/

## Usage:
For ES6 see the examples here:
https://github.com/ErikSom/Clipper2-WASM/tree/main/CPP/clipper2-wasm/examples/es

For UMD see the examples here:
https://github.com/ErikSom/Clipper2-WASM/tree/main/CPP/clipper2-wasm/examples/umd

## Typescript example:
```javascript
import { Clipper2ZFactoryFunction, MainModule } from 'clipper2-wasm/dist/clipper2z';
import * as _Clipper2ZFactory from 'clipper2-wasm/dist/umd/clipper2z';

const Clipper2ZFactory: Clipper2ZFactoryFunction = _Clipper2ZFactory;

Clipper2ZFactory({
	locateFile: () => {
		return 'path/to/your/clipper2z.wasm'
	},
}).then((Clipper2Z: MainModule) => {
	console.log('Clipper2Z', Clipper2Z);
})
```

## Benchmark vs Clipper1 WASM: (Apple M2 Pro)
Clipper1 WASM repository: https://github.com/xaviergonz/js-angusj-clipper
```
clipper1 Intersection EvenOdd 5000 ops 5000 points: 2898.5 ms
clipper2 Intersection EvenOdd 5000 ops 5000 points: 2061.5 ms
28.88% improvement

clipper1 Union EvenOdd 5000 ops 5000 points: 3812.699999988079 ms
clipper2 Union EvenOdd 5000 ops 5000 points: 3094.800000011921 ms
18.83% improvement

clipper1 Difference EvenOdd 5000 ops 5000 points: 3291 ms
clipper2 Difference EvenOdd 5000 ops 5000 points: 2554.699999988079 ms
22.37% improvement

clipper1 Xor EvenOdd 5000 ops 5000 points: 4045.400000035763 ms
clipper2 Xor EvenOdd 5000 ops 5000 points: 3576 ms
11.60% improvement

clipper1 Intersection EvenOdd 10000 ops 100 points: 185 ms
clipper2 Intersection EvenOdd 10000 ops 100 points: 106.40000003576279 ms
42.49% improvement

clipper1 Union EvenOdd 10000 ops 100 points: 236.39999997615814 ms
clipper2 Union EvenOdd 10000 ops 100 points: 141.89999997615814 ms
39.97% improvement

clipper1 Difference EvenOdd 10000 ops 100 points: 209.19999998807907 ms
clipper2 Difference EvenOdd 10000 ops 100 points: 123.40000003576279 ms
41.01% improvement

clipper1 Xor EvenOdd 10000 ops 100 points: 256.60000002384186 ms
clipper2 Xor EvenOdd 10000 ops 100 points: 156.4000000357628 ms
39.05% improvement
```
See implementation: https://github.com/ErikSom/Clipper2-WASM/tree/main/clipper2-wasm/examples/benchmark

Made possible by:
https://github.com/AngusJohnson/Clipper2

Huge thanks to [@Birch-san](https://www.github.com/Birch-san) with an outstanding wasm port example:
https://github.com/Birch-san/box2d-wasm/
