const canvasElement=document.querySelector('canvas');
export const Constant={
    'WIDTH':1000,
    'HEIGHT':600,
}
canvasElement.width=Constant.WIDTH;
canvasElement.height=Constant.HEIGHT;
const canvasContext=canvasElement.getContext('2d');
export {canvasContext}



