import sys
import numpy as np

#maps = ["Accent","Accent_r","Blues","Blues_r","BrBG","BrBG_r","BuGn","BuGn_r","BuPu","BuPu_r","CMRmap","CMRmap_r","Dark2","Dark2_r","GnBu","GnBu_r","Greens","Greens_r","Greys","Greys_r","OrRd","OrRd_r","Oranges","Oranges_r","PRGn","PRGn_r","Paired","Paired_r","Pastel1","Pastel1_r","Pastel2","Pastel2_r","PiYG","PiYG_r","PuBu","PuBuGn","PuBuGn_r","PuBu_r","PuOr","PuOr_r","PuRd","PuRd_r","Purples","Purples_r","RdBu","RdBu_r","RdGy","RdGy_r","RdPu","RdPu_r","RdYlBu","RdYlBu_r","RdYlGn","RdYlGn_r","Reds","Reds_r","Set1","Set1_r","Set2","Set2_r","Set3","Set3_r","Spectral","Spectral_r","Vega10","Vega10_r","Vega20","Vega20_r","Vega20b","Vega20b_r","Vega20c","Vega20c_r","Wistia","Wistia_r","YlGn","YlGnBu","YlGnBu_r","YlGn_r","YlOrBr","YlOrBr_r","YlOrRd","YlOrRd_r","afmhot","afmhot_r","autumn","autumn_r","binary","binary_r","bone","bone_r","brg","brg_r","bwr","bwr_r","cool","cool_r","coolwarm","coolwarm_r","copper","copper_r","cubehelix","cubehelix_r","flag","flag_r","gist_earth","gist_earth_r","gist_gray","gist_gray_r","gist_heat","gist_heat_r","gist_ncar","gist_ncar_r","gist_rainbow","gist_rainbow_r","gist_stern","gist_stern_r","gist_yarg","gist_yarg_r","gnuplot","gnuplot2","gnuplot2_r","gnuplot_r","gray","gray_r","hot","hot_r","hsv","hsv_r","inferno","inferno_r","jet","jet_r","magma","magma_r","nipy_spectral","nipy_spectral_r","ocean","ocean_r","pink","pink_r","plasma","plasma_r","prism","prism_r","rainbow","rainbow_r","seismic","seismic_r","spectral","spectral_r","spring","spring_r","summer","summer_r","terrain","terrain_r","viridis","viridis_r","winter","winter_r"]
maps = ["afmhot","CMRmap","flag","cubehelix","Blues_r","bone","BrBG","BrBG_r","BuGn_r","binary_r","coolwarm","Spectral","Spectral_r","terrain","gist_stern","gnuplot","hot","inferno","plasma","prism","Reds","seismic"]

for cmp in maps:
	# Color mapping
	from matplotlib.cm import ScalarMappable
	
	mycmap = ScalarMappable(cmap=cmp)
	#mycmap.to_rgba([0,1])

	from PIL import Image, ImageDraw
	image_grey = Image.open(sys.argv[1])
	image_grey.load()
	image_grey = image_grey.convert('L')

	image = Image.fromarray(np.uint8(np.array(mycmap.to_rgba(image_grey.getdata())).reshape(*(image_grey.size),4)*255))		

	filename = sys.argv[1].split('.')[0]+'_color_'+cmp+'.bmp'
	print('Saving', filename)
	image.save(filename, "BMP")

	'''image = Image.new("RGB", image_grey.size, (0,0,0))
	draw = ImageDraw.Draw(image)
	for i in range(image_grey.size[0]):
		for j in range(image_grey.size[0]):
			c = image_grey.getpixel((i, j))[0]
			clr = mycmap.to_rgba(c/255)
			draw.point((i, j), (int(255*clr[0]), int(255*clr[1]), int(255*clr[2])))'''