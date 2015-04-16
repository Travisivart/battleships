#ifndef CAMERA_H
#define CAMERA_H


class camera
{
public:
    camera();
    ~camera();

    void translate(float newX, float newY, float newZ);
    void rotate(float newX, float newY, float newZ);

private:

    float transX;
    float transY;
    float transZ;

    float rotX;
    float rotY;
    float rotZ;
};

#endif // CAMERA_H
