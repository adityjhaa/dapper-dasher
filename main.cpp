#include "raylib.h"

//global
const int width = 960, height = 720;

struct animdata{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updatetime,runningtime;
};

bool isonground(animdata data, int height){
    return data.pos.y >= height - data.rec.height;
}

animdata update(animdata data, float dt, int maxframe){
    data.runningtime+=dt;
    if(data.runningtime>=data.updatetime){
        data.runningtime=0.0;
        data.rec.x = data.frame*data.rec.width;
        data.frame++;
        data.frame = data.frame%maxframe;
    }
    return data;
}

int main(){
    InitWindow(width,height,"Dapper-Dasher!");

    
    const int gravity = 3000;
    bool isinair{};
    const int jumpvel = -1000;
    int velocity = 0;
    
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animdata scarfydata{{0.0,0.0,(float) scarfy.width/6,(float) scarfy.height},
                        {width/6,(float) height-scarfy.height},0,1.0/12.0,0.0
    };


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    int nebulavel{-600};

    const int noofnebulae=20; // Choose the number of obstacles here.
    animdata nebulae[noofnebulae]{};

    for(int i = 0; i<noofnebulae ; i++){
        nebulae[i]={{0.0,0.0,(float) nebula.width/8,(float) nebula.height/8},
                     {width + (float)i*700,(float) height-nebula.height/8},0,1.0/16.0,0.0
        };
    }

    float finishline{nebulae[noofnebulae-1].pos.x + 400};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgx{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgx{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgx{};

    bool collision{};
    
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        const float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        bgx -= 50*dt;
        if(bgx <= -background.width*3.75){
            bgx = 0.0;
        }
        Vector2 background1pos{bgx,0.0};
        DrawTextureEx(background,background1pos, 0.0, 3.75, WHITE);
        Vector2 background2pos{bgx + background.width*(float) 3.75, 0.0};
        DrawTextureEx(background,background2pos, 0.0, 3.75, WHITE);

        mgx -= 100*dt;
        if(mgx <= -midground.width*3.75){
            mgx=0.0;
        }
        Vector2 midground1pos{mgx,0.0};
        DrawTextureEx(midground,midground1pos,0.0,3.75,WHITE);
        Vector2 midground2pos{mgx + midground.width*(float) 3.75,0.0};
        DrawTextureEx(midground,midground2pos,0.0,3.75,WHITE);

        fgx -= 200*dt;
        if(fgx <= -foreground.width*3.75){
            fgx=0.0;
        }
        Vector2 foreground1pos{fgx,0.0};
        DrawTextureEx(foreground,foreground1pos,0.0,3.75,WHITE);
        Vector2 foreground2pos{fgx + foreground.width*(float) 3.75,0.0};
        DrawTextureEx(foreground,foreground2pos,0.0,3.75,WHITE);
        

        if(isonground(scarfydata,height)){
            velocity=0;
            // scarfydata.pos.y=height-scarfydata.rec.height;
            isinair=false;

        }else{
            velocity+=gravity*dt;
            isinair=true;
        }
        if(IsKeyDown(KEY_SPACE) and !isinair){
            velocity+=jumpvel;
            
        }
        

        for(animdata nebula: nebulae){
            float padding{50};
            Rectangle nebrec{
                nebula.pos.x + padding,
                nebula.pos.y + padding,
                nebula.rec.width - 2*padding,
                nebula.rec.height - 2*padding
            };
            Rectangle scarfyrec{
                scarfydata.pos.x,
                scarfydata.pos.y,
                scarfydata.rec.width,
                scarfydata.rec.height
            };

            if(CheckCollisionRecs(nebrec,scarfyrec)){
                collision=true;
            }
        }

        scarfydata.pos.y+=velocity*dt;
        
        if(!isinair){
            scarfydata = update(scarfydata,dt,6); 
        }

        for(int i = 0; i<noofnebulae ; i++){
            nebulae[i].pos.x += (nebulavel - i*10)*dt;

            nebulae[i]=update(nebulae[i],dt,8);
        }

        finishline += nebulavel*dt;
        
        if(collision){

            DrawText("GAME OVER!",width/2-240,height/2,80,WHITE);
        
        }else if(scarfydata.pos.x>=finishline){

            DrawText("YOU WIN",width/2-150,height/2,80,WHITE);
        
        }else{

            for(int i = 0; i<noofnebulae ; i++){
                DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,RED);
            }
            DrawTextureRec(scarfy,scarfydata.rec,scarfydata.pos,WHITE);
            
        }
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    return 0;
}