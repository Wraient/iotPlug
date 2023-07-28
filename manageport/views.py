from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import redirect
from django.contrib import admin
from django.urls import path, include
from rest_framework.routers import DefaultRouter
from api.views import ProductViewSet
from api.models import Product
from .db_query_handler import update_product_state, view_db, get_product_data

# Create your views here.


def db_data_for_page():
    the_data = get_product_data()
    return_data = {}
    for package in the_data:
        return_data.update({str(package[1]) : package[0]})

    return return_data


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

    update_product_state(key, action)
    view_db()

    print('clicked')


def access(request, id):
    return HttpResponse(id)

def render_manageport(request):
    # print(request)
    if request.method == 'POST':
        # print('clicked')
        button_value = request.POST.get('port_update')
        port_update(button_value)
        # return redirect("/manageport/#"+button_value.split()[1])
    # print(data)

        # print(button_value)
    
    # print("no")
    # print(request)
    return render(request, 'manageport/index.html', {
        "data_list":db_data_for_page()
    })

def render_404(request, string):
    return HttpResponse("<h1>error 404<h1>")