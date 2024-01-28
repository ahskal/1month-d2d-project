#pragma once
class Camera : public Singleton<Camera>
{
private:
    Viewport            viewport;  
    Matrix              S, V, P, VP;     

public:
    //ī�޶���ġ
    Vector2             position;
    Vector2		        scale;

public:
    Camera();
    void          Set();
    void          ResizeScreen();
    const Matrix& GetP() { return P; };
    const Matrix& GetVP() { return VP; };
};