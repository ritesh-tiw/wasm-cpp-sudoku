import { canvasContext } from "./constants";
import { Constant } from "./constants";


export const draw=({color,position,dimension})=>{
    canvasContext.fillStyle = color;
    canvasContext.fillRect(position.x,position.y,dimension.width,dimension.height);
}

export const update=({color,position,velocity,dimension})=>{
    position.x+=velocity.vx;
    position.y+=velocity.vy;
    draw({color,position,dimension});
    if(position.x>=Constant.WIDTH){
        position.x=0;
    }if(position.x<=-dimension.width){
        position.x=Constant.WIDTH-dimension.width;
    }
}

