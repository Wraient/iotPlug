from django.shortcuts import render
from django.http import HttpResponse
from .models import Appliance
from django.http import JsonResponse

# Create your views here.
def port_update_new(button_value):
    print("button value:",button_value)
    instance_to_edit = Appliance.objects.get(pk=button_value.split()[1])
    print("insatance: ", instance_to_edit)
    if button_value.split()[0] == 'on':
        instance_to_edit.state = True
    else:
        instance_to_edit.state = False
    
    instance_to_edit.save()
    instance_to_edit.save()
    print("updated database: ", view_db_new)

def access(request, id):
    return HttpResponse(Appliance.objects.get(pk=id))

def render_manageport(request):
    # print(request)
    if request.method == 'POST':
        button_value = request.POST.get('port_update') # 'off 1' or 'on 1'
        port_update_new(button_value)
    # print(return_data_for_page())
    return render(request, 'manageport/index.html', {
        "appliances":return_data_for_page()
    })

# {"data": [{"id": 1, "name": "Kids Room Camera"}, ... ]} at return data in db_data_for_page
def return_data_for_page():
    data = list(Appliance.objects.values()) # [{'id': 1, 'state': True}, {'id': 2, 'state': True}]
    # print(data)
    # return_data = {}
    # for i in range(len(data)):
    #     return_data = [str(data[i]["name"])] = int(data[i]["state"])
    return data

def view_db_new(request):
    for i in Appliance.objects.all():
        print(i)

def view_data_json(request):
    data = list(Appliance.objects.values())  # Query all instances and convert to a list of dictionaries
    return JsonResponse({'data': data})

# get {"data": [{"id": 1, "name": "Kids Room Camera", "state": false}, {"id": 2, "name": "School Computers", "state": false}, {"id": 3, "name": "Bedroom Lights", "state": false}, {"id": 4, "name": "Hall TV", "state": true}]}
