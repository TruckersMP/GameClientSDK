<p align="center"><img src="https://truckersmp.com/assets/img/truckersmp-logo-sm.png"></p>

<p align="center">
    <a href="https://docs.truckersmp.com/client-sdk/"><img src="https://img.shields.io/badge/docs-docs.truckersmp.com-blue" alt="Documentation"></a>
    <a href="https://github.com/TruckersMP/GameClientSDK/releases"><img src="https://img.shields.io/github/v/release/TruckersMP/GameClientSDK" alt="Latest release"></a>
</p>

## Introduction

The TruckersMP Client SDK lets you write native plugins for the TruckersMP
client for Euro Truck Simulator 2 and American Truck Simulator. It can react to
game events, read live world state, draw overlays, and extend gameplay systems.

The SDK is header-only. There is nothing to link against; the client binds
everything at runtime through function tables.

## Requirements

- Windows x64
- A C++17 (or newer) compiler; any toolchain producing a Windows x64 DLL works
- The TruckersMP client

## Headers

All headers live in [`include/TruckersMP`](include/TruckersMP). The following
are the public ones that you may include in your build:

| Header | When to include |
| --- | --- |
| `TruckersMP.hxx` | Always. The C++ API: `Session`, typed modules, `std::optional` getters, type-safe events. |
| `Bus.hxx` | Only if your plugin covers bus gameplay. |

The remaining headers (`TruckersMP.h`, `TruckersMP_Bus.h`, `TruckersMP_Base.h`,
`TruckersMP_Runtime.hxx`) are the C interop layer and wrapper internals, there
for binary compatibility between your plugin and the client. The two headers
above pull them in; you do not have to include them yourself. C++ is the
supported wrapper today.

The bus module is gated behind an intent, a named grant that gives a plugin
access to a module. The bus intent is public, so its add-on ships in this
repository. Other intents are granted per project on request; the
[Intents](https://docs.truckersmp.com/client-sdk/advanced/intents) page explains
how to apply.

## Examples

| Example | Shows |
| --- | --- |
| [`general`](examples/general) | Basic SDK usage: getters, events, entity handles, and the bus module add-on. |

Each example is a standalone CMake project; build it with:

```powershell
cmake -B build -A x64
cmake --build build --config Release
```

## Documentation

The full documentation lives at
[docs.truckersmp.com/client-sdk](https://docs.truckersmp.com/client-sdk/). The
[Getting Started](https://docs.truckersmp.com/client-sdk/getting-started) guide
takes to a working plugin; the rest covers core concepts, a reference for every
public module, how-to articles, and the change log for each SDK release.

## Support

Ask questions in the [Discord server](https://discord.gg/truckersmp). Report
bugs on the [issue tracker](https://github.com/TruckersMP/GameClientSDK/issues).

## License

The SDK is released under the [MIT License](LICENSE).
