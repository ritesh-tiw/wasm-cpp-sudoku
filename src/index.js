import { useRef ,useEffect} from "react";
import * as ReactDomClient from "react-dom/client";
import {player,enemy} from "./PlayerData.js";
import constant from "./constants.js";

const draw=(CANVAS_CONTEXT,{color,position,dimension})=>{
      CANVAS_CONTEXT.fillStyle=color;
      CANVAS_CONTEXT.fillRect(position.x,position.y,dimension.width,dimension.height);
}

const App=() =>{
  let ref=useRef(null);

  useEffect(()=>{
    const canvasElement=ref.current;
    const CANVAS_CONTEXT=canvasElement.getContext('2d');
    CANVAS_CONTEXT.fillStyle='black';
    CANVAS_CONTEXT.fillRect(0,0,constant.WIDTH,constant.HEIGHT);
    draw(CANVAS_CONTEXT,player);
    draw(CANVAS_CONTEXT,enemy);
  });

  return(
    <canvas
      ref={ref}
      width={constant.WIDTH}
      height={constant.HEIGHT} 
    />
  )
}


const root=ReactDomClient.createRoot(document.getElementById("root"));
root.render(<App/>);