#include "raylib.h"

int main(){
    const int width = 512, height = 380;
    InitWindow(width,height,"Dapper-Dasher!");

    
    const int gravity = 3000;
    bool isinair{};
    const int jumpvel = -1000;
    int velocity = 0;
    
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebularec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulapos{width,height-nebularec.height};

    int nebulavel{-600};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyrec;
    scarfyrec.width=scarfy.width/6;
    scarfyrec.height=scarfy.height;
    scarfyrec.x=0;
    scarfyrec.y=0;

    Vector2 scarfypos;
    scarfypos.x=(width-scarfyrec.width)/2;
    scarfypos.y=height-scarfyrec.height;

    int frame{0};
    const float updatetime= 1.0/12.0;
    float runningtime{};

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        const float dt = GetFrameTime();


        if(scarfypos.y>=height-scarfyrec.width){
            velocity=0;
            scarfypos.y=height-scarfyrec.width;
            isinair=false;

        }else{
            velocity+=gravity*dt;
            isinair=true;
        }
        if(IsKeyDown(KEY_SPACE) and !isinair){
            velocity+=jumpvel;
            
        }
        
        nebulapos.x += nebulavel*dt;

        scarfypos.y+=velocity*dt;
        
        runningtime+=dt;
        if(runningtime>=updatetime and !isinair){
            runningtime=0.0;
            scarfyrec.x = frame*scarfyrec.width;
            frame++;
            if(frame>5){
                frame=0;
            }
        }


        DrawTextureRec(nebula,nebularec,nebulapos,WHITE);

        
        DrawTextureRec(scarfy,scarfyrec,scarfypos,WHITE);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}