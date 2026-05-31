# UCefViewPlayGround

UCefViewPlayGround is a demo and development host project for the
[UCefView](https://fab.com/s/ec232806c889) Unreal Engine plugin.

UCefView embeds Chromium Embedded Framework (CEF) browser views in Unreal Engine
projects, making it possible to build in-game browsers, web-powered UI, and
HTML-based tools with both UMG and Slate integration.

## What's Included

- Unreal Engine host project files for UE 5.0 through UE 5.8.
- A trial binary build of the UCefView plugin for supported Unreal Engine
  versions.
- Example UCefView widgets, browser window blueprints, actors, and sample web
  resources.
- A first-person playground map for testing browser views in game.

## Quick Start

1. Clone this repository.
2. Open the `.uproject` file that matches your Unreal Engine version, for
   example `UCefViewPG_5_6.uproject`.
3. Let Unreal Engine generate project files if prompted.
4. Open the project and run the included first-person playground map.
5. Explore the UCefView widgets and browser examples under the plugin content.

## Build Notes

The bundled binaries were built with the default preferred Visual C++ toolchain
for each corresponding Unreal Engine version. The table below lists the
recommended Windows MSVC toolchain versions to install when building this
project or regenerating project files.

| Unreal Engine | Preferred VC toolchain | Visual Studio version | Notes |
| --- | --- | --- | --- |
| UE 5.0 | 14.29.30133 | Visual Studio 2019 v16.11.5 | Install `MSVC v142 - VS2019 C++ x64/x86 build tools (v14.29-16.11)`. |
| UE 5.1 | 14.29.30146 | Visual Studio 2019 | Preferred compiler is Visual Studio 2019. |
| UE 5.2 | 14.34.31933 | Visual Studio 2022 v17.4 or newer | Visual Studio 2022 became the default compiler. |
| UE 5.3 | 14.34.31933 | Visual Studio 2022 v17.4 or newer | Same build-farm toolchain as UE 5.2. |
| UE 5.4 | 14.38.33130 | Visual Studio 2022 v17.8 | Preferred MSVC compiler was bumped to 14.38. |
| UE 5.5 | 14.38.33130 | Visual Studio 2022 v17.8 | Matches Epic's UE 5.5 build-farm toolchain. |
| UE 5.6 | 14.38.33130 | Visual Studio 2022 v17.8 | UE 5.6 keeps the UE 5.5 preferred MSVC version. |
| UE 5.7 | 14.44.35207 | Visual Studio 2022 v17.14 or newer | Default Microsoft Visual C++ compiler was updated to MSVC 14.44. |
| UE 5.8 | 14.44.35207 | Visual Studio 2022 v17.14 or newer | Currently follows the UE 5.7 toolchain used by this playground's UE 5.8 build. |

If you run into build or load issues, make sure the matching Visual Studio and
MSVC toolchain for your Unreal Engine version is installed. For source builds or
custom engine installations, regenerate project files before opening the project.

## Documentation

- [UCefView Official Documentation](https://cefview.github.io/UCefView/)
- [UCefView on Fab](https://fab.com/s/ec232806c889)

## Support

For bug reports, feature requests, and usage questions, please use the
[UCefView GitHub Issues page](https://github.com/cefview/UCefView/issues).
