function listDevices() {
	var args = "";
	var xhr = new XMLHttpRequest();
	xhr.open('get', '/usb', true);
	xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
	xhr.onreadystatechange = function () {
		if (xhr.readyState === 4) {
			if(xhr.status == 200) {
				var html = "<h2>List USB devices</h2>";

				var jresult = JSON.parse(xhr.responseText);
				var listArray = jresult.list;
				html += "<table>";
				html +=   "<tr>";
				html +=     "<th>VID</th><th>PID</th>";
				html +=     "<th>Bus</th><th>Port</th><th>Device</th>";
				html +=   "</tr>";
				for(var i = 0; i < listArray.length; i++) {
					var item = listArray[i];
					html += "<tr>";
					html +=   "<td>" + item.vid         + "</td>";
					html +=   "<td>" + item.pid         + "</td>";
					html +=   "<td>" + item.conn_bus    + "</td>";
					html +=   "<td>" + item.conn_port   + "</td>";
					html +=   "<td>" + item.conn_device + "</td>";
					html += "</tr>";
				}
				html += "</table>";
				var divContent = document.getElementById("content");
				divContent.innerHTML = html;
			}
		}
	};
	xhr.send(args);
}
