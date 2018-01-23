.pragma library

function add(p1, p2) {
  return Qt.point(p1.x + p2.x, p1.y + p2.y);
}

function subtract(p1, p2) {
  return Qt.point(p1.x - p2.x, p1.y - p2.y);
}

function negate(p) {
  return Qt.point(-p.x, -p.y);
}

function scale(p, scaling) {
  return Qt.point(p.x * scaling, p.y * scaling);
}

function distance(p1, p2) {
  return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

function round(p) {
  return Qt.point(Math.round(p.x), Math.round(p.y));
}
