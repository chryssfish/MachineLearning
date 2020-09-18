
def plot_kmeans():
	im = images[0]
	ab = []

	for im in images[:1]:
		ab.append(im[:,:,1:].reshape((-1,2)))

	ab = np.concatenate(ab)

	im = images[1]

	kmeans = KMeans(n_clusters=4, random_state=0, n_init=1)
	kmeans.fit(ab)
	new_space = kmeans.cluster_centers_
	im4 = im.copy()

	k = np.reshape(kmeans.predict(im[:,:,1:].reshape((-1,2))), (im.shape[0], im.shape[1], 1))
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			im4[i,j,1] = new_space[k[i,j],0]
			im4[i,j,2] = new_space[k[i,j],1]

	kmeans = KMeans(n_clusters=8, random_state=0, n_init=1)
	kmeans.fit(ab)
	new_space = kmeans.cluster_centers_

	im8 = im.copy()

	k = np.reshape(kmeans.predict(im[:,:,1:].reshape((-1,2))), (im.shape[0], im.shape[1], 1))
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			im8[i,j,1] = new_space[k[i,j],0]
			im8[i,j,2] = new_space[k[i,j],1]


	kmeans = KMeans(n_clusters=16, random_state=0, n_init=1)
	kmeans.fit(ab)
	im16 = im.copy()
	new_space = kmeans.cluster_centers_

	k = np.reshape(kmeans.predict(im[:,:,1:].reshape((-1,2))), (im.shape[0], im.shape[1], 1))
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			im16[i,j,1] = new_space[k[i,j],0]
			im16[i,j,2] = new_space[k[i,j],1]


	kmeans = KMeans(n_clusters=32, random_state=0, n_init=1)
	kmeans.fit(ab)
	im32 = im.copy()
	new_space = kmeans.cluster_centers_

	k = np.reshape(kmeans.predict(im[:,:,1:].reshape((-1,2))), (im.shape[0], im.shape[1], 1))
	for i in range(0,im.shape[0]):
		for j in range(0,im.shape[1]):
			im32[i,j,1] = new_space[k[i,j],0]
			im32[i,j,2] = new_space[k[i,j],1]


	plt.figure()
	plt.subplot(321)
	plt.imshow(cv2.cvtColor(images[0], cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.tight_layout()
	plt.title("Source")


	plt.subplot(322)
	plt.imshow(cv2.cvtColor(im, cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.tight_layout()
	plt.title("Target")

	plt.subplot(323)
	plt.imshow(cv2.cvtColor(im4, cv2.COLOR_LAB2RGB))
	plt.tight_layout()
	plt.axis('off')
	plt.title("Discrete K=4")

	plt.subplot(324)
	plt.imshow(cv2.cvtColor(im8, cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.tight_layout()
	plt.title("Discrete K=8")

	plt.subplot(325)
	plt.imshow(cv2.cvtColor(im16, cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.title("Discrete K=16")
	plt.tight_layout()

	plt.subplot(326)
	plt.imshow(cv2.cvtColor(im32, cv2.COLOR_LAB2RGB))
	plt.axis('off')
	plt.title("Discrete K=32")
	plt.tight_layout()



	plt.show()
