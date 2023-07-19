from django.urls import path
from . import views


urlpatterns = [
    path("port/<int:id>", views.access),
    path("", views.render_manageport),
    path("<str:string>", views.render_404) 
]