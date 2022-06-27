const canvasElem=document.querySelector('canvas');
const canvasContext=canvasElem.getContext('2d');
const CANVAS_HEIGHT=570;
const CANVAS_WIDTH=1056;



canvasElem.width=CANVAS_WIDTH;
canvasElem.height=CANVAS_HEIGHT;


canvasContext.fillStyle='yellow';
canvasContext.fillRect(0,0,canvasElem.width,canvasElem.height);


const checkBoundary=(coordinate,dimension,velocity)=>{
    if(coordinate.x>=canvasElem.width-dimension.width){
        velocity.x=-velocity.x;
    }else if(coordinate.x<=0){
        velocity.x=-velocity.x;
    }
    if(coordinate.y<=0){
        velocity.y=-velocity.y;
    }else if(coordinate.y>=canvasElem.height-dimension.height){
        velocity.y=-velocity.y;
    }
}

const drawRect=({color,velocity,coordinate,dimension})=>{
    canvasContext.fillStyle=color;
    canvasContext.fillRect(coordinate.x,coordinate.y,dimension.width,dimension.height);
    const update=()=>{
        drawRect(player);
        coordinate.x+=velocity.x;
        coordinate.y+=velocity.y;
        checkBoundary(coordinate,dimension,velocity);
    }
    return update;
}


const player={
    'color':'#ffcccb',
    'velocity':{
        'x':0,
        'y':0
    },
    coordinate:{
        'x':10,
        'y':10,
    },
    dimension:{
        'width':100,
        'height':100
    }
}

const enemy={
    'color':'#ADD8E6',
    'velocity':{
        'x':-20,
        'y':-10
    },
    coordinate:{
        'x':canvasElem.width-100,
        'y':canvasElem.height-100,
    },
    dimension:{
        'width':100,
        'height':100
    }
}


const animate=()=>{
    window.requestAnimationFrame(animate);
    canvasContext.fillStyle='yellow';
    canvasContext.fillRect(0,0,canvasElem.width,canvasElem.height);
    const updatePlayer=drawRect(player);
    const updateEnemy=drawRect(enemy);
    updatePlayer();
    updateEnemy()
}

animate();



window.addEventListener('keydown',(e)=>{
    switch(e.key){
        case 'd':
            player.velocity.x=10;
        break;
        case 'a':
            player.velocity.x=-10;
        break;
        case 'w':
            player.velocity.y=-10;
        break;
        case 's':
            player.velocity.y=10;
        break;

        default:
            console.log(e.key);
    }
})

window.addEventListener('keyup',(e)=>{
    switch(e.key){
        case 'd':
            player.velocity.x=0;
        break;
        case 'a':
            player.velocity.x=0;
        break;
        case 'w':
            player.velocity.y=0;
        break;
        case 's':
            player.velocity.y=0;
        break;
        default:
            console.log(e.key);
    }
})