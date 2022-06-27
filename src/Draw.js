import { canvasContext } from "./constants";
import { Constant } from "./constants";
import {canvasBackground} from "./canvas-backGround.js";


export const draw=({color,position,dimension})=>{
    canvasContext.fillStyle = color;
    canvasContext.fillRect(position.x,position.y,dimension.width,dimension.height);
}

export const update=({color,position,velocity,dimension})=>{
    position.x+=velocity.x;
    position.y+=velocity.y;
    draw({color,position,dimension});
}

