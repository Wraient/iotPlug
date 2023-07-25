from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import redirect

# Create your views here.


data = {"1": True, "2": False, "3": False, "4": False, "5": False, "6": False, "7": False, "8": False, "9": False, "10": False}
# data = {"1": True, }


def port_update(button_value):
    print(button_value)
    given_data = button_value.split()
    action = given_data[0]
    key = given_data[1]
    if action == "off": 
        action = False
    else: 
        action = True
    data[key] = action
    print(data)
    print(key, action)

def access(request, id):
    return HttpResponse(id)

def render_manageport(request):
    print(request)
    if request.method == 'POST':
        print('clicked')
        button_value = request.POST.get('port_update')
        port_update(button_value)
        # return redirect("/manageport/#"+button_value.split()[1])
    print(data)

        # print(button_value)
    
    # print("no")
    # print(request)
    return render(request, 'manageport/index.html', {
        "data_list":data
    })

def render_404(request, string):
    return HttpResponse("<h1>error 404<h1>")