#include "gif.h"
AnimatedObject GenerateAnimatedObject(const Texture2D *Sheet, int frameWidth, int frameHeight, float frameDelay,
                                      float startX, float startY, float speedX, float speedY, float finalX,
                                      float finalY)
{
    AnimatedObject obj = {0};

    obj.texture = *Sheet;

    obj.frameCount = obj.texture.width / frameWidth;

    obj.frames = malloc(obj.frameCount * sizeof(Rectangle));

    for (int i = 0; i < obj.frameCount; i++)
    {
        obj.frames[i] = (Rectangle){i * frameWidth, 0, frameWidth, frameHeight};
    }

    obj.frameDelay = frameDelay;
    obj.currentFrame = 0;
    obj.frameTimer = 0;

    obj.posX = startX;
    obj.posY = startY;
    obj.speedX = speedX;
    obj.speedY = speedY;
    obj.finalX = finalX;
    obj.finalY = finalY;

    return obj;
}
AnimatedObject LoadAnimatedObject(const char *fileName, int frameWidth, int frameHeight, float frameDelay, float startX,
                                  float startY, float speedX, float speedY, float finalX, float finalY)
{
    AnimatedObject obj = {0};

    obj.texture = LoadTexture(fileName);

    obj.frameCount = obj.texture.width / frameWidth;

    obj.frames = malloc(obj.frameCount * sizeof(Rectangle));

    for (int i = 0; i < obj.frameCount; i++)
    {
        obj.frames[i] = (Rectangle){i * frameWidth, 0, frameWidth, frameHeight};
    }

    obj.frameDelay = frameDelay;
    obj.currentFrame = 0;
    obj.frameTimer = 0;

    obj.posX = startX;
    obj.posY = startY;
    obj.speedX = speedX;
    obj.speedY = speedY;
    obj.finalX = finalX;
    obj.finalY = finalY;

    return obj;
}

void UpdateAnimatedObject(AnimatedObject *obj)
{
    float dt = GetFrameTime();

    obj->frameTimer += dt;
    if (obj->frameTimer >= obj->frameDelay / 1000.0f)
    {
        obj->frameTimer = 0;
        obj->currentFrame = (obj->currentFrame + 1) % obj->frameCount;
    }

    if ((obj->speedX > 0 && obj->posX < obj->finalX) || (obj->speedX < 0 && obj->posX > obj->finalX))
    {
        obj->posX += obj->speedX * dt;

        if ((obj->speedX > 0 && obj->posX > obj->finalX) || (obj->speedX < 0 && obj->posX < obj->finalX))
        {
            obj->posX = obj->finalX;
        }
    }

    if ((obj->speedY > 0 && obj->posY < obj->finalY) || (obj->speedY < 0 && obj->posY > obj->finalY))
    {
        obj->posY += obj->speedY * dt;

        if ((obj->speedY > 0 && obj->posY > obj->finalY) || (obj->speedY < 0 && obj->posY < obj->finalY))
        {
            obj->posY = obj->finalY;
        }
    }
}

void DrawAnimatedObject(const AnimatedObject *obj, Color tint)
{
        DrawTextureRec(obj->texture, obj->frames[obj->currentFrame], (Vector2){obj->posX, obj->posY}, WHITE);
    
}
void UnloadAnimatedObject(AnimatedObject *obj)
{
    UnloadTexture(obj->texture);
    if(obj->frames!=NULL)
    free(obj->frames);
}
void ResetAnimatedObject(AnimatedObject *obj)
{
    if (obj->frames != NULL)
    {
        free(obj->frames);
        obj->frames = NULL;
    }
    obj->frameCount = 0;
    obj->currentFrame = 0;
}
