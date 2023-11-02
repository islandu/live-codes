async function getClientInfo() {
    const response = await fetch('https://ipinfo.io/json', {
        method: 'GET',
        headers: {
            'user-agent': 'swim'
        }
    })

    return await response.json()
}

function sanitizeData(clientInfo) {
    const propertyLabels = {
        "ip": "IP Address",
        "hostname": "Host Name",
        "city": "City",
        "region": "State/Region",
        "country": "Country",
        "loc": "Location",
        "org": "Provider",
        "postal": "Zip Code",
        "timezone": "Time Zone"
    }

    const sanitized = {}

    for (const property in propertyLabels) {
        if (clientInfo[property]) {
            sanitized[propertyLabels[property]] = clientInfo[property]
        }
    }

    return sanitized
}

async function populateTable() {
    var table = document.getElementById('client-info-table').getElementsByTagName('tbody')[0]
    const clientInfo = sanitizeData(await getClientInfo())

    while (table.firstChild) {
        table.removeChild(table.firstChild)
    }

    for (var key in clientInfo) {
        var row = table.insertRow()
        var label = row.insertCell(0)
        var value = row.insertCell(1)
        label.innerHTML = key
        value.innerHTML = clientInfo[key]
    }
}
