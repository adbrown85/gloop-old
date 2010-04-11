/*
 * AxisAlignedSlab.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;



/**
 * Pair of AxisAlignedPlanes.
 */
public class AxisAlignedSlab extends BasicDrawable
                             implements Drawable {
	
	private AxisAlignedPlane planes[];
	private double halfWidth;
	private Point center, min, max;
	
	
	/**
	 * Creates a new %AxisAlignedSlab.
	 * 
	 * @param center
	 *     Point on an axis that's the center of the slab.
	 * @param width
	 *     Width between the minimum and maximum planes in the slab.
	 */
	public AxisAlignedSlab(Point center,
	                       double width) throws Exception {
		
		super(null, null);
		
		// Copy
		this.center = center;
		
		// Initialize
		halfWidth = width / 2;
		planes = new AxisAlignedPlane[2];
		if (center.x != 0.0) {
			min = new Point(center.x-halfWidth, 0.0);
			max = new Point(center.x+halfWidth, 0.0);
		} else {
			min = new Point(0.0, center.y-halfWidth);
			max = new Point(0.0, center.y+halfWidth);
		}
		planes[0] = new AxisAlignedPlane(min);
		planes[1] = new AxisAlignedPlane(max);
	}
	
	
	/**
	 * Checks if a ray is inside the slab.
	 */
	public boolean contains(Ray ray) {
		
		if (center.x != 0)
			return ray.origin.x >= min.x && ray.origin.x <= max.x;
		else
			return ray.origin.y >= min.y && ray.origin.y <= max.y;
	}
	
	
	/**
	 * Draws the slab.
	 */
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		// Draw each plane
		for (AxisAlignedPlane plane : planes) {
			plane.draw(graphic, dimension);
		}
	}
	
	
	/**
	 * Checks if the slab is intersected by a ray.
	 */
	public IntersectionPair intersectedBy(Ray ray) {
		
		Intersection intersection;
		IntersectionPair intersectionPair;
		
		// Find pair of intersection from planes
		intersectionPair = new IntersectionPair();
		for (int i=0; i<2; ++i) {
			intersection = planes[i].intersectedBy(ray);
			if (intersection != null) {
				intersectionPair.add(intersection);
			}
		}
		
		// Return pair
		if (intersectionPair.empty()) {
			return null;
		} else {
			return intersectionPair;
		}
	}
	
	
	public static void main(String[] args) throws Exception {
		
		AxisAlignedSlab slab=null;
		DisplayFrame display;
		IntersectionPair intersectionPair;
		Ray ray;
		
		// Test
		slab = new AxisAlignedSlab(new Point(100, 0), 50);
		ray = new Ray(new Point(320.0, 240.0),
		              new Vector2D(-1.0, 0.5));
		intersectionPair = slab.intersectedBy(ray);
		if (intersectionPair != null) {
			ray.addIntersectionPair(intersectionPair);
		}
		
		// Show
		display = new DisplayFrame("AxisAlignedPlane", 640, 480);
		display.add(slab);
		display.add(ray);
		display.start();
	}
}
