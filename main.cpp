#include "raylib.h"

//global
const int width = 512, height = 380;

struct animdata{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updatetime,runningtime;
};


int main(){
    InitWindow(width,height,"Dapper-Dasher!");

    
    const int gravity = 3000;
    bool isinair{};
    const int jumpvel = -1000;
    int velocity = 0;
    
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animdata scarfydata{{0.0,0.0,(float) scarfy.width/6,(float) scarfy.height},
                        {width/5,(float) height-scarfy.height},0,1.0/12.0,0.0
    };


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    int nebulavel{-600};

    const int noofnebulae=6;
    animdata nebulae[noofnebulae]{};

    for(int i = 0; i<noofnebulae ; i++){
        nebulae[i]={{0.0,0.0,(float) nebula.width/8,(float) nebula.height/8},
                     {width + (float)i*500,(float) height-nebula.height/8},0,1.0/16.0,0.0
        };
    }

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
        

        scarfydata.pos.y+=velocity*dt;
        
        scarfydata.runningtime+=dt;
        if(scarfydata.runningtime>=scarfydata.updatetime and !isinair){
            scarfydata.runningtime=0.0;
            scarfydata.rec.x = scarfydata.frame*scarfydata.rec.width;
            scarfydata.frame++;
            scarfydata.frame = scarfydata.frame%6;
        }
        for(int i = 0; i<noofnebulae ; i++){
            nebulae[i].pos.x += nebulavel*dt;

            nebulae[i].runningtime+=dt;
            if(nebulae[i].runningtime>=nebulae[i].updatetime){
                nebulae[i].runningtime=0.0;
                nebulae[i].rec.x = nebulae[i].frame*nebulae[i].rec.width;
                nebulae[i].frame++;
                nebulae[i].frame = nebulae[i].frame%8;
            }

            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,RED);
        }
        DrawTextureRec(scarfy,scarfydata.rec,scarfydata.pos,WHITE);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}