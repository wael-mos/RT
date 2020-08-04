# RT

RayTracer project from 42.
<br />
### Install

```bash
brew install gtk+3
brew install adwaita-icon-theme
git clone https://github.com/wael-mos/RT.git ~/RT
cd ~/RT
make
./RT [file]
```
Files are in scenes folder.
<br />
### Hotkeys

"w" "a" "s" "d" to move the camera, "space" to move up, "z" to go down
arrow keys to change the looking direction of the camera
<br />
### Features

When we execute the RayTracer without files, we will see this. You can still choose a file and click on the folder to open it. Or you can create it !

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/window.png" width="640"/>
</p>

We can render different shapes (they are all available in the menu on the left except the Goursat).

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/objects.png" width="640"/>
</p>

We can also render more complex shapes with 4 possible intersection points.
<p align="center">
  <b>Goursat</b>
</p>

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/goursat.png" width="640"/>
</p>

<p align="center">
  <b>Tore</b>
</p>

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/tore.png" width="640"/>
</p>

The lights can have any color and they will interact properly with the world and with each other.

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/multi_lights.png" width="500"/>
  <img src="https://github.com/wael-mos/RT/blob/master/screens/fancy.png" width="500"/>
</p>

All objects can have a transparency and a refraction index.

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/tube.png" width="500"/>
  <img src="https://github.com/wael-mos/RT/blob/master/screens/refract.png" width="500"/>
</p>

They can also have a reflection index.

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/inf_sphere.png" width="500"/>
  <img src="https://github.com/wael-mos/RT/blob/master/screens/infinity.png" width="500"/>
</p>

Objects color and normal vectors can be altered depending on the hitpoint position.
<p align="center">
  <b>Objects color</b>
</p>

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/patterns.png" width="640"/>
</p>

<p align="center">
  <b>Normal perturbation (water effect)</b>
</p>

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/water.png" width="500"/>
  <img src="https://github.com/wael-mos/RT/blob/master/screens/water2.png" width="500"/>
</p>

A perlin texture can be applied to objects.

<p align="center">
  <img src="https://github.com/wael-mos/RT/blob/master/screens/demo_perlin.png" width="640"/>
</p>
Perlin noise is a procedural texture used as a visual effect to increase the apparent realism in image synthesis.
