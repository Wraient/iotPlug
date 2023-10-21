from django.urls import path
from . import views


urlpatterns = [
    path("port/<int:id>", views.access),
    path("", views.render_manageport, name="manageport"),
    path("show_data/", views.view_data_json, name="show_data"),
    # path("<str:string>", views.render_404),
]