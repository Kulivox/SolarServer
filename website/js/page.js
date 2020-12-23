$("#mainTable").ready(function () {
    $.get("?mainTable", function (data, status) {
        $("#mainTable").append(data);
    })
});
