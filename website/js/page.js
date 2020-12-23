$("#mainTable").ready(function () {
    $.get("mainPage?mainTable", function (data, status) {
        $("#mainTable").append(data);
    })
});
