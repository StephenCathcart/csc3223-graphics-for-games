##CSC3223 Graphics for Games

###Screenshots
![Shader 1](https://github.com/StephenCathcart/csc3223-graphics-for-games/blob/master/screenshots/shader1.png)

![Shader 1](https://github.com/StephenCathcart/csc3223-graphics-for-games/blob/master/screenshots/shader2.png)

![Shader 3](https://github.com/StephenCathcart/csc3223-graphics-for-games/blob/master/screenshots/shader3.png)

###Controls
L = Lines/Fill
N = Show normals
T = Swap from normal texture rendering to advanced texture rendering
1 = Swap shader to basic
Insert = Alpha up
Delete = Alpha down
Home = Light up
End = Light down

###Features
- A rotating cube.
- A vertex shader which modulates the scale of objects over time, using a uniform variable.
- A geometry shader which generates further cubes from the inputted vertices.
- A geometry shader which modulates the cubes x,y and z distances
- A fragment shader which blends back and forth between two textures.
- A fragment shader which using phong lighting.
Features when pressing N
- A fragment shader which uses the normal as colours.
Features when pressing T
- A fragment shader which uses a third, greyscale texture to determine blend levels
Features when pressing 1
- The program reloads a different vertex and fragment shader.
- The cube now has a rotation around world space rather than its own origin.
- The fragment shader allows the cube to now have different coloured sides.
- The cube has a fully transparent face which you can see its other faces through.
- The fragment shader now increases/reduces the alpha of the cubes colour.
- The fragment shader now increases/reduces lights intensity.

###Referenced images
- Wall texture: http://i1245.photobucket.com/albums/gg581/jamesmcd85/Brick_texture_notTiled.jpg
- Wood texture: http://th02.deviantart.net/fs16/200H/f/2007/221/b/9/Wood_Texture_by_Dellot.jpg