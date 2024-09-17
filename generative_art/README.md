This piece of generative art is meant to abstractly depict a battle occuring in space. The central, large structure made of glass cube/prism layers is meant to convey a sense of scale, and the small spiked green objects are intended to evoke an image of alien spacecraft attacking the large ship in the center. 

The main spaceship is made by interpolating colors and drawing randomly generated length/width rectangles within a grid based on randomly generated frame sizes and layer thickness parameters. Additionally, each section has a 1/2 probabilty of being "tapered" which gives some segments the trapezoidal look (my intention was that these would look like engines and such). All randomly generated parameters are scaled by the display length and width so that in effect, we are just randomly sampling the ratios rather than their absolute values.

The aliens are also randomly generated, and the number of aliens depends on the screen resolution/size. They are made by shooting off spheres from a randomly sampled center, and the diameter of these spheres decays with the distance from the center. 

The JavaScript is run on boot by launching a bash script using autostart by adding the following lines to ~/.config/wayfire.ini:

```bash
[autostart]
autostart_wf_shell = false
chromium = /home/student334/Documents/cs334/generative_art/display_on_boot.sh
```

I tried to use systemd for this purpose as we did in lab, but since it launches in headless mode, I could not get chromium to launch and kept getting errors like ERROR:gbm_wrapper.cc(257). The wayfire.ini file was really helpful, and plan to use this in the future instead of systemd unless I encounter some compelling reason not to.

Citations:
1. https://editor.p5js.org/mtchl/sketches/S1Lfx04il
2. https://editor.p5js.org/martaverde/sketches/GGGaqpyAr