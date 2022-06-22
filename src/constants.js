const canvasElement=document.querySelector('canvas');
export const Constant={
    'WIDTH':1056,
    'HEIGHT':576,
}
canvasElement.width=Constant.WIDTH;
canvasElement.height=Constant.HEIGHT;
const canvasContext=canvasElement.getContext('2d');
export {canvasContext}



