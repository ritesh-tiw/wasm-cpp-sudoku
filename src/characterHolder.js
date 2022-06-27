import { draw,update } from "./Draw.js";
import { player } from "./PlayerData.js";
import { enemy } from "./PlayerData.js";
import { canvasBackground } from "./canvas-backGround.js";

export const characterHolder = () => {
    draw(player);
    draw(enemy);
}


export const animate = () => {
    window.requestAnimationFrame(animate);
    canvasBackground('yellow');
    update(player);
}




