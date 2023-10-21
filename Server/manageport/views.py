from django.shortcuts import render
from django.http import HttpResponse
from .models import Appliance
from django.http import JsonResponse


# Create your views here.
def port_update_new(button_value):
    instance_to_edit = Appliance.objects.get(pk=button_value.split()[1])
    if button_value.split()[0] == 'on':
        instance_to_edit.state = True
    else:
        instance_to_edit.state = False
    
    instance_to_edit.save()
    print(view_db_new)

def access(request, id):
    return HttpResponse(Appliance.objects.get(pk=id))

def render_manageport(request):
    # print(request)
    if request.method == 'POST':
        button_value = request.POST.get('port_update') # 'off 1' or 'on 1'
        port_update_new(button_value)

    return render(request, 'manageport/index.html', {
        "data_list":return_data_for_page()
    })

# {'1': 1, '2': 0, '3': 1, '4': 1} at return data in db_data_for_page
def return_data_for_page():
    data = list(Appliance.objects.values()) # [{'id': 1, 'state': True}, {'id': 2, 'state': True}]
    return_data = {}
    for i in range(len(data)):
        return_data[str(data[i]["id"])] = int(data[i]["state"])
    return return_data  

def view_db_new(request):
    for i in Appliance.objects.all():
        print(i)

def view_data_json(request):
    data = list(Appliance.objects.values())  # Query all instances and convert to a list of dictionaries
    return JsonResponse({'data': data})

# get [{"id":1,"state":true},{"id":2,"state":false},{"id":3,"state":true},{"id":4,"state":true}] at api/products/?format=json