#include "raylib.h"

struct animdata{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updatetime,runningtime;
};


int main(){
    const int width = 512, height = 380;
    InitWindow(width,height,"Dapper-Dasher!");

    
    const int gravity = 3000;
    bool isinair{};
    const int jumpvel = -1000;
    int velocity = 0;
    
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    animdata nebdata{{0.0,0.0,nebula.width/8,nebula.height/8},{width,height-nebula.height/8},0,1.0/12.0,0.0};

    int nebulavel{-500};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animdata scarfydata{{0.0,0.0,scarfy.width/6,scarfy.height},{width/5,height-scarfy.height},0,1.0/12.0,0.0};




    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        const float dt = GetFrameTime();


        if(scarfydata.pos.y>=height-scarfydata.rec.width){
            velocity=0;
            scarfydata.pos.y=height-scarfydata.rec.width;
            isinair=false;

        }else{
            velocity+=gravity*dt;
            isinair=true;
        }
        if(IsKeyDown(KEY_SPACE) and !isinair){
            velocity+=jumpvel;
            
        }
        
        nebdata.pos.x += nebulavel*dt;

        scarfydata.pos.y+=velocity*dt;
        
        scarfydata.runningtime+=dt;
        if(scarfydata.runningtime>=scarfydata.updatetime and !isinair){
            scarfydata.runningtime=0.0;
            scarfydata.rec.x = scarfydata.frame*scarfydata.rec.width;
            scarfydata.frame++;
            scarfydata.frame = scarfydata.frame%6;
        }


        nebdata.runningtime+=dt;
        if(nebdata.runningtime>=nebdata.updatetime){
            nebdata.runningtime=0.0;
            nebdata.rec.x = nebdata.frame*nebdata.rec.width;
            nebdata.frame++;
            nebdata.frame = nebdata.frame%8;
        }

        DrawTextureRec(nebula,nebdata.rec,nebdata.pos,WHITE);
        
        DrawTextureRec(scarfy,scarfydata.rec,scarfydata.pos,WHITE);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}