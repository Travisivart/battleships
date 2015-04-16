Readme for Assignment 4 - Travis Neely

Camera Settings tab:

Lighting:
You can turn on and off lighting by clicking the Lighting checkbox (default:on).

Camera Translation:
You can use the sliders or the edit boxes to translate the camera along the x, y, or z axis.
The Reset button restores the translation values to 0.
This uses the glTranslatef function.

Camera Rotation:
You can use the sliders or the edit boxes to rotate the camera along the x, y, or z axis. Valid values are from -360 to +360.
The Reset button restores the rotation values to 0.
This uses the glRotatef function.

Camera Zoom:
You can use the Zoom slider or edit box to zoom the camera in or out. Valid values are from 5 to 5000.
This uses the glOrtho function.

Aspect Ratio:
You can change the aspect ratio of the camera by adjusting the Width and Height sliders.
This uses the glOrtho function.

Z-Clipping:
You can change the z-clipping by adjusting the near and far sliders.
This uses the glOrtho function.


Object setting tab:

You can load an object by clicking the "Load Object" button and navigating to an .obj file. Loaded models will display in the list box at the top of the Object Settings tab.
By selecting a model in the list box tab, you will be able to perform the various animations on it. Whichever model is selected in the list box, will have the Translation,
Rotation, Scale, and Animation paths applied to it.

Model Options allow for all models to be displayed as either their Vertices, a Wireframe object, or the model (with material applied if a material file exists). Click
the radio button to select which type of model you want to display. It is applied instantly and applies to all models on the screen which are loaded from .obj files.

The Sierpinski object can be created by clicking on the "Load Sierpinski" button. You can select a Depth value from 1 to 8 which is the number of recursions. The object can be cleared
clicking the Clear Screen button under the General Settings tab.

Translation:
Enter an x, y, z value and click Translate to translate the selected model. The object will be moved to the center and an animation will play out the translation function.

Rotation:
Enter an x, y, z value and click Rotate to rotate the selected model. The object will be moved to the center and an animation will play out the rotation function.

Scale:
Enter an scaling value and click Scale to scale the selected model. An animation will play out the scaling function.