import cv2
import cv2.cv as cv
import numpy as np


class VisionTracker:

	def __init__(self, cameraNumber):
		self.capture = cv2.VideoCapture(cameraNumber)

	def run(self):
		windowScaleFactor = .3
		# Capture first frame to get size
		_, rawImage = self.capture.read()
		frameSize = (rawImage.shape[1], rawImage.shape[0])
		print frameSize

		windowSize = tuple(int(i*windowScaleFactor) for i in frameSize)

		while True:
			_, rawImage = self.capture.read()
			cv2.imshow("Raw", cv2.resize(rawImage, windowSize))

			# Convert the image to grayscale.
			blobImage = cv2.cvtColor(rawImage, cv.CV_RGB2GRAY)

			# Smooth to get rid of false positives
			cv2.blur(blobImage, (15, 15), blobImage)

			equalized = cv2.equalizeHist(blobImage)
			blobImage = equalized/2 + blobImage/2

			cv2.imshow("Equalized Average", cv2.resize(blobImage, windowSize))

			# Convert the image to black and white.
			cv2.threshold(blobImage, 40, 255, cv.CV_THRESH_BINARY_INV, blobImage)

			cv2.imshow("Thresholded", cv2.resize(blobImage, windowSize))

			# Dilate and erode to get people blobs
			cv2.dilate(blobImage, np.ones((18, 18), 'int8'), blobImage)
			cv2.erode(blobImage, np.ones((10, 10), 'int8'), blobImage)

			contours, _ = cv2.findContours(blobImage, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

			annotated = rawImage.copy()
			cv2.drawContours(annotated, contours, -1, (0,255,0), -1)

			points = None
			for contour in contours:
				m = cv2.moments(contour)
				centroid = np.array([[m['m10']/m['m00'], m['m01']/m['m00']]], np.float32)
				if points == None:
					points = centroid
				else:
					points = np.vstack((points, centroid))
				intCentroid = (int(centroid[0][0]), int(centroid[0][1]))
				cv2.circle(annotated, intCentroid, 20, (255,0,0), 5)

			if points != None and points.shape[0] >= 4:
				corners = np.array([[0,0],
									[0, frameSize[1]],
									[frameSize[0], 0],
									frameSize], np.float32)

				cornerPoints = None
				for corner in corners:
					bestDist = float('inf')
					bestPoint = None
					for point in points:
						dist = np.linalg.norm(corner - point)
						if dist < bestDist:
							bestDist = dist
							bestPoint = point
					if cornerPoints == None:
						cornerPoints = bestPoint
					else:
						cornerPoints = np.vstack((cornerPoints, bestPoint))

				transform = cv2.getPerspectiveTransform(cornerPoints, corners)

				transformedImage = cv2.warpPerspective(rawImage, transform, frameSize)
				cv2.imshow("Transformed", cv2.resize(transformedImage, windowSize))

			cv2.imshow("Annotated", cv2.resize(annotated, windowSize))

			# Listen for ESC key
			c = cv2.waitKey(7) % 0x100
			if c == 27:
				break



if __name__ == "__main__":
	vt = VisionTracker(0)
	vt.run()


