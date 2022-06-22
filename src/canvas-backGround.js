import {canvasContext} from "./constants.js";
import {Constant} from "./constants.js";

export const canvasBackground=(color)=>{
    canvasContext.fillStyle = color===null?'black':color;
    canvasContext.fillRect(0,0,Constant.WIDTH,Constant.HEIGHT);
}