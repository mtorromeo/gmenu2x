var website = {};

website.home = function() {
	var slideshow = document.id('slideshow');
	var curIdx = 0;
	var imgs = slideshow.getElements('img');
	
	imgs.each(function(img) {
		img.set('tween', {duration: 1000}).set('title', img.get('alt'));
	});
	
	function nextImage() {
		var curImg = imgs[curIdx];
		curIdx++;
		if (curIdx >= imgs.length)
			curIdx = 0;
		var nextImg = imgs[curIdx];
		curImg.tween('opacity', 0);
		nextImg.tween('opacity', 1);
		nextImage.delay(6000);
	}
	
	nextImage();
}

website.routes = {
	'^/(gmenu2x/)?(index\.html)?$': website.home
}

$H(website.routes).each(function(v, k) {
	var r = new RegExp(k);
	if (r.test(window.location.pathname))
		v();
});