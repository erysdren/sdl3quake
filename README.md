# sdl3quake

modernized faithful Quake sourceport utilizing SDL3 and C23 features

## Notes

- lacks 64-bit stability
- lacks audio
- lacks netplay
- lacks all extended Quake engine features from the past 29 years
- does not actually use SDL3 yet

## Building

```shell
cmake -Bcmake-build -DCMAKE_BUILD_TYPE=Release .
cmake --build cmake-build --target sdl3quake
```

## Credits

- [quakegeneric](https://github.com/erysdren/quakegeneric)
- [qrustyquake](https://github.com/cyanbun96/qrustyquake)
- special thanks to @bruxisma for CMakeLists.txt wrangling

## Command Line Arguments

| Name             | Arguments                             | Description                                                   |
|------------------|---------------------------------------|---------------------------------------------------------------|
| `-surfcachesize` | \[surface cache size in kilobytes\]   |                                                               |
| `-zone`          | \[zone memory size in kilobytes\]     |                                                               |
| `-dedicated`     | \[maximum number of clients\]         | enables dedicated server mode                                 |
| `-listen`        | \[maximum number of clients\]         | enables listen server mode                                    |
| `-particles`     | \[maximum number of particles\]       |                                                               |
| `-minmemory`     | \[minimum available memory in bytes\] | if the engine cannot allocate this much memory, it will abort |
| `-safe`          |                                       | enables safe mode                                             |
| `-condebug`      |                                       | log all console messages to `qconsole.log`                    |
| `-port`          | \[port number\]                       |                                                               |
| `-udpport`       | \[udp port number\]                   |                                                               |
| `-ipxport`       | \[ipx port number\]                   |                                                               |
| `-hipnotic`      |                                       | load mission pack 1 data (scourge of armagon)                 |
| `-rogue`         |                                       | load mission pack 2 data (dissolution of eternity)            |
| `-game`          | \[game directory\]                    | load additional game data from specified directory            |
| `-path`          | \[directory or pak file\] \[...\]     | add specified directories or pak files to engine hierarchy    |
| `-basedir`       | \[base directory\]                    | overrides engine base directory                               |

## License

Copyright (C) 1996-1997 Id Software, Inc.\
Copyright (C) 2025 erysdren (it/its)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see https://www.gnu.org/licenses/
