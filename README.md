# GLSL

By Buttburger

***1. Lightmap 7/28/2023***

-Inital uploads

***2. Bezier and Multiple Mesh 7/28/2023***

-Inital uploads

-[DeCastlejau Bezier curve](https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c) drawn in dots

-Load multiple objects in 1 file

***3. Playback Hermite 7/28/2023, 10/27/2023***

-Inital uploads

-Playback, curve point color swap, can play backwards

-Hermite curve added

-Fix reuploaded as Playback_Hermite2

***4. LocRotScale Animation 10/19/2023***

-2 point curve animation [Linear interpolation](https://javascript.info/bezier-curve) P = (1-t)P1 + tP2

-Added X button to orbit around object, Z to switch back

***5. Interpolation 11/25/2023***

-Animation interpolation employing the use of [Hermite Cubic Splines](https://github.com/gszauer/GameAnimationProgramming)

-Moved from Quaternions to Euler

-Provided 3 files, rename to use

-Switched to grey background, black text

***6. VertexColors 1/24/2024***

-Load solid colors from vertex paint

-Looks for either UV Maps or Vertex Colors. Not meant to load both

-Switched to light grey background

***7. Multiple Mesh Rewrite 2/21/2024***

-Merged drawVBO_light to drawVBO

-Moving away from limitOne and meshSkip

-Fixed indices for lighting

-Screen size adjust on resize

-Object load has transform matrix applied

***8. Light casters and normal mapping 3/17/2024***

-File name shortened

-Added directional light, point light, and spot light

-Added normal mapping

-To move directional light use keys I, J for X axis. O, K for Y axis. P, L for Z axis. Point light is fixed. Spot light use arrow keys and mouse drag

-4/30/2024 GL_DEPTH_TEST and GL_CULL_FACE fix in drawVBO

***9. Multiple Objects Animation 9/16/2024***

-Load multiple objects with animation in 1 file

***10. Object Matrix 10/12/2024***

-Load objects without mesh such as camera and lamp (light) with its matrix and animation

***11. Object Matrix fix 10/19/2024***

-A fix to load assets correctly

***12. Multiple Lights 11/16/2024***

-Blender lamp (light): point, sun (directional), and spot. Spotlight direction not implemented

-Locate the lights with spheres

***13. Spotlight direction 12/11/2024***

-Spot light direction applied

***14. Animate Camera 1/19/2024***

-Movement keys switch to WASD. For camera animation press C, press X to orbit, press Z to revert to inital. Press or hold Q or E to adjust down or up animation speed.
