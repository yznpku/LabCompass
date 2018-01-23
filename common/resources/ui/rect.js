.pragma library

function ltrb(left, top, right, bottom) {
  return Qt.rect(left, top, right - left, bottom - top);
}

function ltwh(left, top, width, height) {
  return Qt.rect(left, top, width, height);
}

function left(rect) {
  return rect.x;
}

function top(rect) {
  return rect.y;
}

function right(rect) {
  return rect.x + rect.width;
}

function bottom(rect) {
  return rect.y + rect.height;
}

function translate(rect, point) {
  return ltwh(rect.x + point.x, rect.y + point.y, rect.width, rect.height);
}

function center(rect) {
  return Qt.point(rect.x + rect.width / 2, rect.y + rect.height / 2);
}

function topLeft(rect) {
  return Qt.point(rect.left, rect.top);
}

function topRight(rect) {
  return Qt.point(rect.right, rect.top);
}

function bottomLeft(rect) {
  return Qt.point(rect.left, rect.bottom);
}

function bottomRight(rect) {
  return Qt.point(rect.right, rect.bottom);
}

function contains(rect, p1, p2) {
  if (p2 !== undefined) {
    return p1 >= rect.x && p1 <= rect.x + rect.width &&
           p2 >= rect.y && p2 <= rect.y + rect.height;
  } else {
    return p1.x >= rect.x && p1.x <= rect.x + rect.width &&
           p1.y >= rect.y && p1.y <= rect.y + rect.height;
  }
}

function pointDistance(p1, p2) {
  return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

function boundingCircleRadius(rect, circlePos) {
  return Math.max(pointDistance(topLeft(rect), circlePos),
                  pointDistance(topRight(rect), circlePos),
                  pointDistance(bottomLeft(rect), circlePos),
                  pointDistance(bottomRight(rect), circlePos));
}

function boundingBox(item) {
  return Qt.rect(item.x, item.y, item.width, item.height)
}
