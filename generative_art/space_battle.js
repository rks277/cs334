let spaceshipLayer;
let spaceshipHeight, spaceshipWidth, spaceshipLayerDepth;
let tapered;
let color1, color2, color3;
let lerpedColor, lerpedColor2;
let angle = 0;
let posX2, posY2;
let speedX2, speedY2;
let scaleFactor;
let points = [];
let accel = 0.9;
let bounce = -1;

function setup() {
  createCanvas(900, 900);
  
  // Canvas for each spaceship layer
  spaceshipLayer = createGraphics(400, 400);
  resetSpaceshipLayer();
  spaceshipLayerDepth = int(random(40, 70)); 

  color1 = color(250, 120, 50, 50);  // Orange for explosions
  color2 = color(255);  // White
  color3 = color(0);    // Black
  
  lerpedColor = lerpColor(color1, color2, 0.8);
  lerpedColor2 = lerpColor(color1, color3, 0.8);
  
  imageMode(CENTER);
  
  background(0);
  
  posX2 = 0;
  posY2 = 900;

  speedX2 = random(-1, 1); 
  speedY2 = random(-3, -1);

  // Drawing the stars in the background
  for (let i = 0; i < width; i += 40) {
    for (let j = 0; j < height; j += 40) {
      strokeWeight(random(0.5, 2));
      stroke(lerpedColor);
      point(i + random(-30, 30), j + random(-30, 30));
    }
  }
}

function draw() {
  
  // Draw the green flow field
  drawFlowField();
  
  
  if (frameCount % spaceshipLayerDepth == 0) resetSpaceshipLayer();
  
  if (tapered > 50) scaleFactor *= 0.995;
  
  posX2 += speedX2 + 4;
  posY2 += speedY2;

  let displacement2 = map(cos(angle), -1, 1, 0, PI);
  tower(displacement2);

  lerpedColor2 = lerpColor(color1, color3, 0.8);

  angle += 0.1;

  // Drawing the spaceship on the main canvas
  blendMode(DIFFERENCE);
  image(spaceshipLayer, posX2, posY2, width * scaleFactor, height * scaleFactor);

  // Update and draw explosions
  for (let p of points) {
    if (p.y > height || p.y < 0) p.ydrift *= bounce;
    if (p.x > width || p.x < 0) p.xdrift *= bounce;

    let diam = max(0, 9 + 40 / p.age);
    fill(255);
    stroke(color(0, 128, 100));
    ellipse(p.x, p.y, diam, diam);

    p.x += p.xdrift;
    p.y += p.ydrift;
    p.xdrift *= accel;
    p.ydrift = p.ydrift * accel;
    p.age++;
  }
}

function tower(move) {
  spaceshipLayer.stroke(255);
  spaceshipLayer.strokeWeight(1);
  
  for (let i = 0; i < spaceshipLayer.width; i += 100) {
    for (let j = spaceshipLayer.height; j > 0; j -= 50) {
      spaceshipLayer.fill(lerpedColor2);
      spaceshipLayer.rect(i, j, spaceshipWidth, spaceshipWidth);
    }
  }
}

function resetSpaceshipLayer() {
  tapered = random(0,100);
  scaleFactor = random(0.2, 0.5);
  spaceshipLayer.clear();
  spaceshipHeight = random(20, 100);
  spaceshipWidth = random(20, 100);
}

function mousePressed() {
  goBoom(mouseX, mouseY);
}

function goBoom(xpos, ypos) {
  for (let i = 0; i < 20; i++) {
    points.push({ 
      x: xpos + random(-2, 2), 
      y: ypos + random(-2, 2), 
      xdrift: random(-10, 10),
      ydrift: random(-10, 10),
      age: 1
    });
  }
}

// Function to draw the flow field starting from the origin
function drawFlowField() {
  stroke(0, 255, 0);  // Set the flow field to green
  strokeWeight(1);
  
  for (let x = 0; x < width; x += 20) {
    for (let y = 0; y < height; y += 20) {
      let angle = atan2(y - height / 2, x - width / 2); // Calculate angle based on the origin
      let vec = p5.Vector.fromAngle(angle); // Create a vector from the angle
      vec.setMag(15); // Set the length of the vector
      line(x, y, x + vec.x, y + vec.y); // Draw the flow line
    }
  }
}
