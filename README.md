# splat

Convert .ppm, .jpeg, .jpg, .png files to .webp.

### Usage

``` shell
make
splat [OPTIONS] [TARGET] SOURCE
```

Arguments:</br>
  SOURCE             File or directory to convert</br>
  TARGET             Output file or directory (optional)</br>

Options:</br>
  -o, --output PATH    Output path for file conversions (file/directory).</br>
  -q, --quality VALUE  Quality of output file (default is 100%).</br>
  -r, --recursive      Process directories recursively.</br>
  -f, --force          Overwrite existing files.</br>
  -d, --dry-run        Show what would be done without doing it.</br>
  -h, --help           Shows help message.</br>
  
## Ideas:
- show the difference in file sizes after conversion

## TODO:
- Add colors to output of test scripts

## Roadmap:
- [ ] Add RAW format support (need height and width from user).
- [ ] Enable conversions between all types.

## Notes:
- If adding more formats, separate parsing into src/formats/"format".c
