from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import random

app = FastAPI()

state = {"battery_status": {}, "panel_status": {0: 1, 1:0, 2:1, 3:0}, "timestamp": "2025.01.01 00:00 AM"}

for i in range(17):
    state["battery_status"][i] = {
        "voltage": round(random.uniform(10.0, 14.4), 1),
        "charging": random.randint(0, 1),
    }

print(state)

app.mount("/static", StaticFiles(directory="/srv/app/static"), name="static")
# Get Jinja2Templates object
templates = Jinja2Templates(directory="/srv/app/templates")


@app.get("/", response_class=HTMLResponse)
async def serve_root(request: Request):
    return templates.TemplateResponse(
        request=request, name="index.html", context={"state": state}
    )

@app.get("/logBatteryState")
async def set_battery_voltage(battery_number: int, voltage: float, charging: bool):
    if battery_number in state["battery_status"]:
        state["battery_status"][battery_number]["voltage"] = voltage
        state["battery_status"][battery_number]["charging"] = int(charging)
        print(state["battery_status"])
        return {"message": "Battery voltage updated successfully"}
    else:
        return {"error": "Battery number not found"}
    
@app.get("/logPanelUsage")
async def set_battery_voltage(panel_number: str, in_use: bool):
    if panel_number in state["panel_status"]:
        state["panel_status"]["panel_number"] = int(in_use)
        return {"message": "Battery voltage updated successfully"}
    else:
        return {"error": "Battery number not found"}

