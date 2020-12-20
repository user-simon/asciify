<p align="center">
<img src="img/title.png" width="75%">
</p>

---

## asciify is a simple command-line tool to create ascii art from .png files. 

Beyond just the input and output files, you can specify downsampling (pixels per character essentially), supersampling (higher value -> smoother or blurrier image, depending on how you see it, but the text file takes longer to generate), and whether to invert the generated ascii (for dark backgrounds).

## Usage
Either launch it as you would any other executable and enter asked-for values or launch it from the command-line as such:

```
asciify [input file] [output file] [downsampling] [supersampling] [OPTIONAL: invert]
```

After running the program, the generated text will be saved to the specified `output file` path. Generally I'd recommend playing around with the downsampling and supersampling for a bit to get the desired effect.

## Notes
Not all fonts are created equal. The ["pixel characters" that I have decided on using](https://github.com/usercynical/asciify/blob/main/main.cpp#L11) were "tuned" using Consolas, as such  there could be other fonts in which the order of the characters should be different, though it seems to work well enough for most (read: all) monospaced fonts that I have tried.

Also keep in mind that Notepad++ sometimes stretches the characters at some zoom levels so if you're having issues with the output images looking a bit *wonky*, try some different zoom levels.

:warning: **It absolutely will not work as intended with a non-monospaced font however** :warning:
(Though admittedly it can lead to some interesting results. Attempt it at your own peril.)

## Building
This project uses C++17 and the [lvandeve/lodepng](https://github.com/lvandeve/lodepng) library mentioned in Credit but other than that, there's not much to it.

## Credit
[lodepng](https://github.com/lvandeve/lodepng) by [lvandeve](https://github.com/lvandeve) is used to load bitmaps from .png files.

The photograph used in the background of the title image ([img/title.png](img/title.png)) is [by Aióny Haust and features Aidana Sahari](https://astanatimes.com/2019/09/innovative-kazakh-photographer-draws-inspiration-from-art-music-and-connecting-with-his-subjects/).

## Examples
These were generated from various source images with various settings and were screenshot in Notepad++ using the font Consolas:

<p align="center">
<img src="img/examples.png" width="80%">
</p>
