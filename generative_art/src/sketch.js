// Inspiration for alien spaceships: https://editor.p5js.org/mtchl/sketches/S1Lfx04il
// Inspiration for main spaceship: https://editor.p5js.org/martaverde/sketches/GGGaqpyAr

let spaceshipLayer;
let spaceshipHeight, spaceshipWidth, spaceshipLayerDepth;
let tapered;
let c1, c2, c3;
let white, color_;
let posX2, posY2;
let speedX2, speedY2;
let scaleFactor;
let points = [];
let accel = 0.9;
let bounce = -1;
let numAliens = 5;
let alienPositions = [];

function setup() {
  createCanvas(windowWidth, windowHeight);
  
  if (width * height < 1000) {numAliens = 0}
  else {numAliens = int(width / 400)}
  
  spaceshipLayer = createGraphics(width * 0.4, height * 0.4);
  resetSpaceshipLayer();
  spaceshipLayerDepth = int(random(width * 0.04, width * 0.07) / 5); 
  c1 = color(250, 120, 50, 50);
  c2 = color(255);
  c3 = color(0);
  white = lerpColor(c1, c2, 0.8);
  color_ = lerpColor(c1, c3, 0.8);
  imageMode(CENTER);
  background(0);
  posX2 = 0;
  posY2 = height;
  speedX2 = width * random(-1, 1) / 900; 
  speedY2 = height * random(-3, -1) / 900;
  for (let i = 0; i < width; i += 40) {
    for (let j = 0; j < height; j += 40) {
      strokeWeight(random(0.5, 2));
      stroke(white);
      point(i + random(-30, 30), j + random(-30, 30));
    }
  }
  for (let i = 0; i < numAliens; i++) {
    alienPositions.push(createVector(random(width), random(height)));
  }
}

function draw() {
  if (frameCount % spaceshipLayerDepth == 0) resetSpaceshipLayer();
  if (tapered > 50) scaleFactor *= 0.995;
  
  posX2 += speedX2 + 2 * width / 900;
  posY2 += speedY2;
  spaceship();
  color_ = lerpColor(c1, c3, 0.8);

  // Drawing the spaceship on the main canvas
  blendMode(DIFFERENCE);
  image(spaceshipLayer, posX2, posY2, width * scaleFactor, height * scaleFactor);

  // Update and draw alien spaceships
  for (let p of points) {
    let diam = max(0, 9 + 40 / p.age);
    fill(color(0, 255, 0));
    stroke(color(106, 22, 184));
    ellipse(p.x, p.y, diam, diam);
    p.x += p.xdrift;
    p.y += p.ydrift;
    p.xdrift *= accel;
    p.ydrift = p.ydrift * accel;
    p.age++;
  }
  if (frameCount == 300) {
    for (let pt of alienPositions) {
      alien(pt.x, pt.y);
    }
  }
  if (frameCount == 350) noLoop();
}

function spaceship() {
  spaceshipLayer.stroke(255);
  spaceshipLayer.strokeWeight(1);
  
  for (let i = 0; i < spaceshipLayer.width; i += spaceshipLayer.width * 0.25) {
    for (let j = spaceshipLayer.height; j > 0; j -= spaceshipLayer.height * 0.125) {
      spaceshipLayer.fill(color_);
      spaceshipLayer.rect(i, j, spaceshipWidth, spaceshipWidth);
    }
  }
}

function resetSpaceshipLayer() {
  tapered = random(0,100);
  scaleFactor = random(0.2, 0.5);
  spaceshipLayer.clear();
  spaceshipHeight = random(0.1, 0.2) * spaceshipLayer.height;
  spaceshipWidth = random(0.1, 0.2) * spaceshipLayer.width;
}

function alien(xpos, ypos) {
  for (let i = 0; i < 5; i++) {
    points.push({ 
      x: xpos + random(-2, 2), 
      y: ypos + random(-2, 2), 
      xdrift: random(-10, 10),
      ydrift: random(-10, 10),
      age: 1
    });
  }
}