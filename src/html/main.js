function listDevices() {
	var args = "";
	var xhr = new XMLHttpRequest();
	xhr.open('get', '/usb', true);
	xhr.onreadystatechange = function () {
		if (xhr.readyState === 4) {
			if(xhr.status == 200) {
				var divContent = document.getElementById("content");
				divContent.innerHTML = xhr.response;
			}
		}
	};
	xhr.send(args);
}
