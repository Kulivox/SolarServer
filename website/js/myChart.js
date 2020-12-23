let ctx = document.getElementById('myChart').getContext('2d');

var chartData;

function getData() {
    $.get("mainPage?activePowerUsageChart", function (data, result) {
        console.log(data);
        let returnedJSON = JSON.parse(data);

        let myLineChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: returnedJSON.labels,
                datasets: [{
                    label: "Aktívna záťaž meniča",
                    data: returnedJSON.data,
                    fill: false
                }],
            },

            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: true
                        }
                    }]
                }
            }
        });

    })
}


getData();


