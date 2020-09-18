import os
import sys
import cv2
import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from skimage.segmentation import slic
from skimage.segmentation import mark_boundaries
import scipy.ndimage
from scipy import ndimage as ndi
from sklearn.svm import SVC
from sklearn.decomposition import PCA
import helpers
# ----------------- Fortoma Train kai Test eikonwn kai Metatropi tous ------------#
images = []
DIR = "tulips" # poies eikones diavazume
train_num = 2 # arithmos training eikonwn
test_num = 1 # arithmos testing eikonwn
test_images = []

for file in sorted(os.listdir(DIR))[:train_num]:
	I = cv2.imread(os.path.join(DIR,file))
	I = cv2.cvtColor(I, cv2.COLOR_BGR2LAB) # metatropi se xoro LAB
	images.append(I)

for file in sorted(os.listdir(DIR))[train_num:test_num+train_num]:
	I = cv2.imread(os.path.join(DIR,file))
	I = cv2.cvtColor(I, cv2.COLOR_BGR2LAB)

	test_images.append(I)

num_images = len(images)

ab = []

# ------------------ Diakritopoiisi Xorou ab ---------------#
for im in images:
	ab.append(im[:,:,1:].reshape((-1,2)))

ab = np.concatenate(ab)

kmeans = KMeans(n_clusters=8, random_state=0, n_init=10)
kmeans.fit(ab)

# --------------------- nea xrwmata - pirines ----------------#
new_space = kmeans.cluster_centers_

X = []
y = []
numSegments = 500

for im in images:
	# ------- euresi twn kentrwn pou antistoixei kathe pixel kai xrwmatismos ek neou tis eikonas --------#
	k = np.reshape(kmeans.predict(im[:,:,1:].reshape((-1,2))), (im.shape[0], im.shape[1], 1))

	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			im[i,j,1] = new_space[k[i,j],0]
			im[i,j,2] = new_space[k[i,j],1]

	# euresi twn superpixel
	segments = slic(im, n_segments = numSegments, sigma = 1)

	# ----- super pixels plot ------ #
	# fig = plt.figure("Superpixels -- %d segments" % (numSegments))
	# ax = fig.add_subplot(1, 1, 1)
	# plt.tight_layout
	# ax.imshow(mark_boundaries(cv2.cvtColor(im, cv2.COLOR_LAB2RGB), segments))
	# plt.axis("off")
	# plt.show()

	#---------------- euresi surf features -------------------#

	surf = cv2.xfeatures2d.SURF_create()
	surf.setExtended(True)
	surf.setHessianThreshold(500)
	SURF_WINDOW=20
	f = []
	# print(im[:,:,0].size)
	v = 0

	surf_features = np.zeros((im.shape[0], im.shape[1], 128))

	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			pos = (i,j)
			kp = cv2.KeyPoint(pos[0], pos[1], SURF_WINDOW)
			_, des1 = surf.compute(im[:,:,0], [kp])
			if des1 is None:
				des1 = np.zeros((1,128))
				v+=1
			surf_features[i,j,:] = des1[0]


	#---------------- euresi gabor features -------------------#

	def compute_feats(image, kernels):
		feats = []
		for k, kernel in enumerate(kernels):
			filtered = ndi.convolve(image, kernel, mode='wrap')
			feats.append(filtered)
		return np.stack(feats,axis=2)



	from skimage.filters import gabor_kernel
	kernels = []
	for theta in range(7):
		theta = 7 / 8. * np.pi
		for frequency in (1/2, 1/3, 1/4, 1/5, 0.05):
			kernel = np.real(gabor_kernel(frequency, theta=theta))
			kernels.append(kernel)
	gabor_im = compute_feats(im[:,:,0], kernels)

	#---------------- variance  -------------------#


	var_w = np.zeros((im.shape[0],im.shape[1]));
	window_size = 5;
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			a = i-2
			c = i+2
			b = j-2
			d = j+2
			if a < 0:
				a = 0
			if b < 0:
				b = 0
			if c >= im.shape[0]:
				c = im.shape[0]-1
			if d >= im.shape[0]:
				d = im.shape[1]-1

			im_patch = im[a:c,b:d,0]
			var_w[i,j] = np.var(im_patch)

	# ------ dimiourgia pinaka xaraktiristikwn ------#
	for i in range(np.max(segments)):
		l = np.where(segments == i)
		features = np.mean(gabor_im[l],axis=0)

		# superpixel mean
		feat_mean = np.mean(im[l])

		feat_var = np.var(var_w[l])

		features = np.concatenate((features, [feat_mean], [feat_var]))
		X.append(features)
		y.append(np.bincount(k[l].squeeze()).argmax())



from sklearn.preprocessing import StandardScaler

scaler = StandardScaler() # kanonikopoiisi tou dataset
scaler.fit(X)
X = scaler.transform(X)

# training twn SVM
clf = SVC(C=1,gamma="auto")
clf.fit(X, y) 

# voithitiki sinartisi gia plot sto telos
def pp(image1, image2):

	fig = plt.figure()
	plt.subplot(121)
	plt.imshow(cv2.cvtColor(cv2.cvtColor(image1, cv2.COLOR_LAB2RGB), cv2.COLOR_RGB2GRAY), cmap='gray')
	plt.axis('off')
	plt.tight_layout()
	plt.title("Gray")
	plt.subplot(122)
	plt.imshow(cv2.cvtColor(image2, cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.tight_layout()
	plt.title("Recolored")
	plt.show()


for im in test_images:
	X_test = []
	segments = slic(im, n_segments = numSegments, sigma = 1)
	#---------------- surf features -------------------#

	surf = cv2.xfeatures2d.SURF_create()
	surf.setExtended(True)
	surf.setHessianThreshold(500)
	SURF_WINDOW=20
	v = 0

	surf_features = np.zeros((im.shape[0], im.shape[1], 128))

	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			pos = (i,j)
			kp = cv2.KeyPoint(pos[0], pos[1], SURF_WINDOW)
			_, des1 = surf.compute(im[:,:,0], [kp])
			if des1 is None:
				des1 = np.zeros((1,128))
				v+=1
			surf_features[i,j,:] = des1[0]

	def compute_feats(image, kernels):
		feats = []
		for k, kernel in enumerate(kernels):
			filtered = ndi.convolve(image, kernel, mode='wrap')
			feats.append(filtered)
		return np.stack(feats,axis=2)

	#---------------- gabor features -------------------#

	gabor_im = compute_feats(im[:,:,0], kernels)

	#---------------- variance  -------------------#

	var_w = np.zeros((im.shape[0],im.shape[1]));
	window_size = 5;
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			a = i-2
			c = i+2
			b = j-2
			d = j+2
			if a < 0:
				a = 0
			if b < 0:
				b = 0
			if c >= im.shape[0]:
				c = im.shape[0]-1
			if d >= im.shape[0]:
				d = im.shape[1]-1

			im_patch = im[a:c,b:d,0]
			var_w[i,j] = np.var(im_patch)

	y_test = []

	# ------ dimiourgia pinaka xaraktiristikwn ------#

	for i in range(np.max(segments)):
		l = np.where(segments == i) # vriskoume ta pixel pou anikun se auto to superpixel
		features = np.mean(gabor_im[l],axis=0)

		feat_mean = np.mean(im[l])

		feat_var = np.var(var_w[l])

		features = np.concatenate((features, [feat_mean], [feat_var]))


		X_test.append(features)


	X_test = scaler.transform(X_test)
	predict = clf.predict(X_test)


	# -------------------------- COLORIZE ------------------------------ #


	original = im.copy()
	im[:,:,1] = 0
	im[:,:,2] = 0

	for i in range(np.max(segments)):
		for j in range(0,im.shape[0]):
			for n in range(0,im.shape[1]):
				if segments[j,n] == i:
					im[j,n,1] = new_space[predict[i],0]
					im[j,n,2] = new_space[predict[i],1]

	pp(original,im)


